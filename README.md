# MQTT Wrapper Library

## Summary

The general purpose of this library is to provide a common interface for several different implementations of MQTT libraries to provide stability and ease of maintainability.

## Assumptions

* The publishers and subscribers are implemented as class templates that are templated based on the message type. The message type must have the following attributes:
  * A member function called `getPayload` with no parameters and a C-string return type. It's probably easiest to derive a class from the provided Message class.

## Procrastinated Issues

* Doxygen comments. Things are too unstable right now and mostly self-descriptive to bother with adding in doxygen comments, but once things are a little more stable it would be really nice to have.
* I'm toying with the idea of turning this wrapper into an actual implementation. It would be nice to have a full(-ish)-featured MQTT library that doesn't require another library to work and it sounds like it would be kinda fun...