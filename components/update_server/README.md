# Update Server

**NOTE**: Requires you to initalize the network stack before start.

## Handlers

I added simple static C++ wrappers around what is basically just c for each of these handlers with the hopes that I would be able to control their lifecycle in a relatively clean manner. I haven't done that yet, but heres to hoping.

### Hello Handler

This is a simple hello world handler to validate that things are working. It was the first one I implimented, but really only serves as an example of a get endpoint now.

### Update Handler

Here is the meaty goodness. It is basically just a Frnkenstine's monster created from the [esp-idf native ota](https://github.com/espressif/esp-idf/tree/master/examples/system/ota/native_ota_example) example. I didn't want the complexity of hosting a server for devices that will ultimatly always be away from wifi access points, and will really only interact with the network behind a planned app.

I reworked the example so that it accepts data from a post call rather than a get request, but the bulk remains the same. The check code (the stuff that makes sure the boot sequence went right) is coppied into the project main. `TODO: Link to main here`
