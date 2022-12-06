#include "application/Application.h"

/*
    class names ideas for this project
    This will be a tree visualizer with a viewport and a tree editor on the side
    - TreeVisualizer
    - TreeEditor
    - TreeViewer
    - TreeEditorViewer
    - TreeEditorVisualizer
    - TreeEditorViewerVisualizer
    - Window

*/

// Taken from https://github.com/ocornut/imgui/issues/707

int main()
{
    return TreeVisualizer::Application::Get().Play();
}