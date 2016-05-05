# Stamplay Ionic Starter

<table>
  <tbody>
    <tr>
    <th>
    <img width="150" src="https://camo.githubusercontent.com/57b8db003e874395844d8ff15e06f4d135060c89/68747470733a2f2f692e696d67736166652e6f72672f643862393933372e706e67" />
    </td>
    <th>
    <img width="150" src="https://camo.githubusercontent.com/4d1bb4177ebbcb7214a4a7af92b0d5d2e7515354/68747470733a2f2f692e696d67736166652e6f72672f643961393161312e706e67" />
    </td>
    <th>
    <img width="150" src="https://camo.githubusercontent.com/90a2be18a3bcac579ee081744abab68dd0652f15/68747470733a2f2f692e696d67736166652e6f72672f643738646137342e706e67" />
    </td>
    </tr>
  </tbody>
</table>



The Stamplay Ionic Starter kit is a simple way to get a Stamplay Ionic project up off the ground.

The starter kit comes with a fully featured task list, based on user accounts. If a user does not wish to create an account, they may use the shared guest Task list to manage their tasks by adding, updating, deleting and marking them complete or incomplete.

Setup Instructions

1. Clone and cd into repo: `git clone https://github.com/Stamplay/stamplay-ionic-starter.git`
2. Run `npm install -g ionic`
4. Run `ionic platform add ios android`
5. Run `npm install && gulp install`
6. Run `stamplay init`, add Stamplay app credentials
7. In the `www/index.html`, update the `Stamplay.init("YOUR APP ID")` to include your `APP ID`
8. Inside the Stamplay Editor, add a `task` object schema with:
  - **title** - *string*
  - **body** - *string*
  - **complete** - *boolean*
9. Run `ionic serve --lab -p 8080`
10. If you are new to Stamplay, or Ionic, we recommend following our [tutorial of this starter kit here](https://blog.stamplay.com/mobile-development-with-ionic-stamplay/).

#### Enjoy!
