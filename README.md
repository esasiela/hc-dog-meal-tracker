# hc-dog-meal-tracker

The HC Dog Meal Tracker is a very simple device designed to track whether the pups have been fed breakfast and dinner.  When our family members have differing schedules, it is easy to loose track of these things.  The days of sticky notes are over!

Adafruit 5v Trinket (very small Arduino clone) controls the system.  There is a single push button, debounced using HC Bouncy Button library, and two LED indicators to show the state.

## Homepage

More details about the project, including some spiffy pictures are at [Hedge Court](https://www.hedgecourt.com/robots/dogMealTracker/).

## States

There are four states:
* 0 - Reset - no meals served, dogs anxious
* 1 - Breakfast - dogs had breakfast today, still anxious for their supper
* 2 - Dinner Only - dogs definitely had dinner, but when the human servant arrived at the Dog Meal Tracker, the breakfast light was not illuminated.  Either a forgetful human servant at breakfast time forgot to press the button, or maybe a really weird day where the duration between breakfast and dinner exceeded the timeout and the system reset
* 3 - Breakfast and Dinner - the dogs are happy and full, but they'll never object to some treats

Press the button to cycle through the states.

## Daily Reset

There are inactivity timeouts to reset the indicator daily:
* Spend no more than 15 hours in state 1
* Spend no more than 8 hours in states 2/3
* Whenever a state expires, reset back to 0

## Examples

Consider a standard use case:
* Breakfast is served around 7am.  If nothing else happens that day, reset after 15 hours, at 10pm.
* Dinner is served around 6pm.  Well within the breakfast timeout, now the timer resets after 8 hours, at 2am.

Early breakfast use case:
* Breakfast served at 5am. reset after 15 hours, 8pm.
* As long as dinner is served before 8pm, we're fine.

Late breakfast use case:
* Breakfast served at noon. Whew, really slept in there, didn't we? If nothing else that day, reset after 15 hours, at 3am.

Late dinner use case:
* Luck pups really never get their supper later than 8pm, which coincides with the early breakfast use case.  I think the pups are golden!

Plus, in extreme cases the family is likely communicating about schedules anyway since they're out of the ordinary routine.


