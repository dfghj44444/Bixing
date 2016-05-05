angular.module('starter.controllers', [])

.controller('AccountController', ["AccountService", "$state", "$rootScope", "$ionicLoading", "$ionicPopup", function(AccountService, $state, $rootScope, $ionicLoading, $ionicPopup) {

  var errorHandler = function(options) {
    var errorAlert = $ionicPopup.alert({
      title: options.title,
      okType : 'button-assertive',
      okText : "Try Again"
    });
  }

  var vm = this;

  vm.login = function() {
    $ionicLoading.show();
    Stamplay.User.login(vm.user)
    .then(function(user) {
      $rootScope.user = user;
      $state.go("tasks");
    }, function(error) {
      $ionicLoading.hide();
      errorHandler({
        title : "<h4 class='center-align'>Incorrect Username or Password</h4>"
      })
    })
  }

  vm.signup = function() {
    $ionicLoading.show();
    Stamplay.User.signup(vm.user)
    .then(function(user) {
      $rootScope.user = user;
      $state.go("tasks");
    }, function(error) {
      errorHandler({
        title : "<h4 class='center-align'>A Valid Email and Password is Required</h4>"
      })
      $ionicLoading.hide();
    })
  }

  vm.logout = function() {
    $ionicLoading.show();
    var jwt = window.location.origin + "-jwt";
    window.localStorage.removeItem(jwt);
    AccountService.currentUser()
    .then(function(user) {
      $rootScope.user = user;
      $ionicLoading.hide();
    }, function(error) {
      console.error(error);
      $ionicLoading.hide();
    })
  }
}])

.controller('HomeController', ["TaskService", "$ionicLoading", "$rootScope", "$state", function(TaskService,  $ionicLoading, $rootScope, $state) {
  var vm = this;

  var findIndex = function(id) {
    return vm.tasks.map(function(task) {
      return task._id;
    }).indexOf(id);
  }

  // Display loading indicator
  $ionicLoading.show();

  vm.setActive = function(id) {
    vm.active = id;
  }

  function removeActive() {

  }

  // Fetch Tasks
  vm.fetch = function() {
    if(!$rootScope.user) {
      // Get all tasks for guests.
      TaskService.getGuestTasks()
      .then(
        function(response) {
          var tasks = response.data;
          vm.tasks = [];
          tasks.forEach(function(item, idx, array) {
            item.dt_create = new Date(item.dt_create).getTime();
            vm.tasks.push(array[idx]);
          });
          $ionicLoading.hide();
        }, function(error) {
          $ionicLoading.hide();
        })
      } else {
        // Get only the user signed in tasks.
        TaskService.getUsersTasks()
        .then(
          function(response) {
            var tasks = response.data;
            vm.tasks = [];
            tasks.forEach(function(item, idx, array) {
              item.dt_create = new Date(item.dt_create).getTime();
              vm.tasks.push(array[idx]);
            });
            $ionicLoading.hide();
          }, function(error) {
            $ionicLoading.hide();
          })
        }
      }



      // Mark Complete a task.
      vm.deleteTask = function(id) {
        $ionicLoading.show();
        vm.tasks.splice(findIndex(id), 1);
        TaskService.deleteTask(id)
        .then(function() {
          $ionicLoading.hide();
        }, function(error) {
          $ionicLoading.hide();
        })
      }

      vm.setStatus = function(task) {
        task.complete = task.complete ? !task.complete : true;
        TaskService.patchTask(task)
        .then(function(task) {
        }, function(error) {
        })
      }


    }])

.controller('TaskController', ["TaskService", "$ionicLoading", "$rootScope", "$state", "$stateParams", function(TaskService,  $ionicLoading, $rootScope, $state, $stateParams) {
  var vm = this;

  if($stateParams.id) {
    $ionicLoading.show();
    TaskService.getTask($stateParams.id)
      .then(function(task) {
        $ionicLoading.hide();
        vm.task = task.data[0];
      }, function(err) {
        $ionicLoading.hide();
        console.error(err);
      })
  }

  // Add a task.
  vm.add = function() {
    $ionicLoading.show();
    TaskService.addNew(vm.task)
    .then(function(task) {
      $ionicLoading.hide();
      $state.go("tasks", {}, { reload: true });
    }, function(error) {
      $ionicLoading.hide();
    })
  }

  vm.save = function() {
    $ionicLoading.show();
    TaskService.updateTask(vm.task)
    .then(function(task) {
      $ionicLoading.hide();
      $state.go("tasks", {}, { reload: true });
    }, function(error) {
      $ionicLoading.hide();
    })
  }





}])
