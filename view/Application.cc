#include "Application.h"
#include "../parser/Parser.h"

bool Application::OnInit() {
    // Create the main application window
    Frame *frame = new Frame("Simple wxWidgets App");
    // Show it
    frame->Show(true);

    // Start the event loop to begin processing user input
    return true;
}
