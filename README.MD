# Miniload AS/RS Client

This miniload AS/RS Client is made to control 2-5 "agoran" named robots that do warehouse operations, the client does not talk to them directly, rather instead it talks to a c# dotnet backend that will be the true source of truth and it will actually communicate with the bots.
the purpose of this client is just to visually represent the state of the warehouse, allow the users to easily change, manually control and check the state, and also to help users deal with errors and issues that may happen while operating the robots.

## in practice
Each agoran has the ability to go to the storage and grab a tray, and then carry it and place it on one of the workstations (there are 2 workstations per agoran). each agoran is responsible for an area in the warehouse, they do not overlap with each other. (which is why there are 2 workstations per agoran)
agorans commands set is quite simple and consists of mainly:
- go to xy location and grab Z (or don't grab, essentialy making it a move command)
- go to xy location and push to Z (or don't push current load, essentialy making it a move command)
- turn on and forget previous errors

the client should not worry about xyz locations or specific command details, as those are handled by the backend. the client uses traynumbers and agoran number and side for commands.

## the vision
the UI should have a card for each agoran, repressenting their state, aswell as a section that is a little seperate that repressents the left and right workstations of each agoran, which could have a tray on them or have no try (None)

the UI should also have a top bar that allows the user to change the mode of each agoran, aswell as a button to send a manual command to each agoran.

the UI should also have a log window that shows the communication between the client and the backend, aswell as any errors that may have occurred.

## Prerequisites
- Windows 10