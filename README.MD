# Miniload AS/RS Client

This miniload AS/RS Client is made to control 2-5 "agoran" named robots that do warehouse operations, the client does not talk to them directly, rather instead it talks to a c# dotnet backend that will be the true source of truth and it will actually communicate with the bots.
the purpose of this client is just to visually represent the state of the warehouse, allow the users to easily change, manually control and check the state, and also to help users deal with errors and issues that may happen while operating the robots.

## in practice
* Request from sap
* Validate request, invalid -> respond with error, don't start task
* valid -> start task
* success -> send async response
* failure -> update agoran status to error
* validate if agoran failed in bad status (holding tray when it shouldn't, not holding tray when it should)
* if no -> jump to recovery from safe path
* if yes -> jump to recovery from unsafe path

safe_path:

the client should not worry about xyz locations or specific command details, as those are handled by the backend. the client uses traynumbers and agoran number and side for commands.

## the vision
the UI should have a card for each agoran, repressenting their state, aswell as a section that is a little seperate that repressents the left and right workstations of each agoran, which could have a tray on them or have no try (None)

the UI should also have a top bar that allows the user to change the mode of each agoran, aswell as a button to send a manual command to each agoran.

the UI should also have a log window that shows the communication between the client and the backend, aswell as any errors that may have occurred.

## Prerequisites
- Windows 10


### TODO
- Add auto pulling for agoran Statuses at all times, different thread, mutex on statuses (even though this will be the only one accessing them?)
- Add auto pulling for agoran logs based on last seen ID, as to not pull anything unnecessary limit to message from last 48 hours (maybe add option in client to increase limit?), also mutex (probably unnecessary)
- define logic for manual mode (send request then wait for response?)
- add logic for buttons to send manual commands (double check on backend, make sure main thread is not blocked)

