//
// Created by abdoulayedia on 03.12.2022
//
#include "Window.h"

namespace TreeVisualizer {
Window::Window() {
  constexpr unsigned int width = 2560;
  constexpr unsigned int height = 1600;

  _window =
      new sf::RenderWindow(sf::VideoMode(width, height), "Tree Visualizer",
                           sf::Style::Default, sf::ContextSettings(0, 0, 8));
  _window->setFramerateLimit(60);
  _window->setVerticalSyncEnabled(true);

  _view = sf::View(sf::FloatRect(0, 0, width, height));
  _view.setCenter(width / 2, height / 2);
  _window->setView(_view);

  if (!ImGui::SFML::Init(*_window)) {
    std::cout << "Error initializing ImGui-SFML" << std::endl;
    exit(1);
  }

  auto &io = ImGui::GetIO();
  // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.IniFilename = "../src/config/imgui.ini";

  _imguiFont = io.Fonts->AddFontFromFileTTF(
      "../src/assets/fonts/Poppins/Poppins-Regular.ttf", 20);
  _font.loadFromFile("../src/assets/fonts/Poppins/Poppins-Regular.ttf");

  if (!ImGui::SFML::UpdateFontTexture()) {
    std::cerr << "No luck\n";
  }

  // increase the font size
  io.FontGlobalScale = 1.5f;

  _shape.setRadius(10.f);
  _shape.setPointCount(50);

  setFancyImguiStyle();

  InitTree();
}

Window::~Window() {
  ImGui::SFML::Shutdown();
  // clear the nodes
  // print the reference count of the nodes
  _nodes.clear();
}

void Window::Play() {
  if (_window == nullptr)
    return;

  while (_window->isOpen()) {
    HandleEvents();
    Update();
    Render();
  }
}

void Window::setFancyImguiStyle() {

  ImGui::GetStyle().FrameRounding = 4.0f;
  ImGui::GetStyle().GrabRounding = 4.0f;

  ImGui::GetStyle().FramePadding = ImVec2(6, 4);
  ImGui::GetStyle().ItemSpacing = ImVec2(6, 2);
  ImGui::GetStyle().ItemInnerSpacing = ImVec2(6, 4);
  ImGui::GetStyle().IndentSpacing = 6.0f;

  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
  colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void Window::InitTree() {
  // init binary tree of height 4
  // std::vector<std::string> treeVec = {
  //     "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
  //     "O", "Hello"};

  // std::vector<std::string> vec = {""};
  // std::vector<std::string> combinaisons =
  // TreeNode::WordCombinations("ABC_CBA", vec);
  _root = TreeNode::FromVector(TreeNode::WordCombinations("abcd"));
  // print reference count of root
  std::cout << "ref count of root: " << _root.use_count() << std::endl;
  // _root = TreeNode::CombinaisonTree("Homer");

  // DFS to add nodes to the vector
  std::stack<std::shared_ptr<TreeNode>> stack;
  stack.push(_root);
  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    _nodes.push_back(node);
    if (node->right)
      stack.push(node->right);
    if (node->left)
      stack.push(node->left);
  }
}

void Window::HandleEvents() {
  if (_window == nullptr)
    return;

  sf::Event event{};
  while (_window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(*_window, event);

    switch (event.type) {
    case sf::Event::Closed:
      _window->close();
      break;
    case sf::Event::KeyPressed:
      switch (event.key.code) {

      case sf::Keyboard::Escape:
        _window->close();
        break;
      // left right top to move _selectedNode
      case sf::Keyboard::Left:
        if (_selectedNode != nullptr && _selectedNode->left)
          _selectedNode = _selectedNode->left;
        break;
      case sf::Keyboard::Right:
        if (_selectedNode != nullptr && _selectedNode->right)
          _selectedNode = _selectedNode->right;
        break;
      case sf::Keyboard::Up:
        if (_selectedNode != nullptr && _selectedNode->parent)
          _selectedNode = _selectedNode->parent;
        break;
      // space to add a child
      case sf::Keyboard::Space:
        if (_selectedNode != nullptr && _selectedNode->left == nullptr) {
          _selectedNode->left = std::make_shared<TreeNode>("New");
          _selectedNode->left->parent = _selectedNode;
          _nodes.push_back(_selectedNode->left);
        } else if (_selectedNode != nullptr &&
                   _selectedNode->right == nullptr) {
          _selectedNode->right = std::make_shared<TreeNode>("New");
          _selectedNode->right->parent = _selectedNode;
          _nodes.push_back(_selectedNode->right);
        }
        break;
      case sf::Keyboard::BackSpace:
        if (_selectedNode != nullptr) {
          // remove from vector
          _nodes.erase(std::remove(_nodes.begin(), _nodes.end(), _selectedNode),
                       _nodes.end());
          // remove from tree
          if (_selectedNode->parent != nullptr) {
            if (_selectedNode->parent->left == _selectedNode)
              _selectedNode->parent->left = nullptr;
            else if (_selectedNode->parent->right == _selectedNode)
              _selectedNode->parent->right = nullptr;
          } else {
            _root = nullptr;
          }
          _selectedNode = nullptr;
        }

        break;
      default:
        break;
      }
      break;
    case sf::Event::Resized:
      _window->setView(
          sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
      break;
    default:
      break;
    }
  }
}

void Window::Update() {
  if (_window == nullptr)
    return;

  ImGui::SFML::Update(*_window, _clock.restart());
}

void Window::Render() {
  if (_window == nullptr)
    return;

  ImGui::PushFont(_imguiFont);
  ImGui::DockSpaceOverViewport();

  ImGui::ShowDemoWindow();
  MenuBar();

  // viewport full window width and height
  ImVec2 viewportSize = ImVec2(_window->getSize().x, _window->getSize().y);

  static uint16_t nodeSize = 20;
  static uint16_t treeWidth = viewportSize.x / 2.f;
  static ImVec2 nodeMargin = {1, 100};
  static float nodeRadius = 25;
  static ImVec2 treePos = {viewportSize.x / 2, viewportSize.y / 2.f};

  sf::RenderTexture rt{};

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
  // make the viewport not resizable nor scrollable
  if (ImGui::Begin("Viewport", nullptr,
                   ImGuiWindowFlags_NoScrollbar |
                       ImGuiWindowFlags_NoScrollWithMouse |
                       ImGuiWindowFlags_NoResize)) {
    viewportSize = ImGui::GetWindowSize();
    rt.create(viewportSize.x, viewportSize.y,
              sf::ContextSettings{0, 0, 0, 3, 0});
    treePos = {viewportSize.x / 2,
               viewportSize.y / 2.f - _root->GetHeight() * nodeRadius};

    // text info about the viewport, cursor position, etc in a corner of the
    // viewport
    if (ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoResize)) {
      ImGui::Text("Cursor position: (%.1f, %.1f)", ImGui::GetMousePos().x,
                  ImGui::GetMousePos().y);
      ImGui::Text("Viewport size: (%.1f, %.1f)", viewportSize.x,
                  viewportSize.y);
      ImGui::Text("Tree size: (%.1f, %.1f)", treeWidth, viewportSize.y);
      ImGui::Text("Node size: (%.1f, %.1f)", nodeSize, nodeSize);
      ImGui::Text("Node margin: (%.1f, %.1f)", nodeMargin.x, nodeMargin.y);
      ImGui::Text("Node radius: %.1f", nodeRadius);
      ImGui::Text("Tree position: (%.1f, %.1f)", treePos.x, treePos.y);
      ImGui::End();
    }

    _mousePos =
        sf::Vector2f(ImGui::GetMousePos().x - ImGui::GetWindowPos().x,
                     ImGui::GetMousePos().y - ImGui::GetWindowPos().y * 2);

    for (int i = 0; i < viewportSize.x; i += 100) {
      for (int j = 0; j < viewportSize.y; j += 100) {
        sf::RectangleShape rect{{100, 100}};
        rect.setPosition(i, j);
        rect.setFillColor(sf::Color(255, 255, 255, 25));
        rect.setOutlineThickness(1);
        rect.setOutlineColor(sf::Color(100, 100, 100, 50));
        rt.draw(rect);
      }
    }

    for (auto &node : _nodes) {
      node->GetShape().setFillColor(sf::Color::White);
      node->Update(_mousePos);
    }

    if (_selectedNode) {
      // floating info window on the node
      ImGui::SetNextWindowPos(
          ImVec2(_selectedNode->GetShape().getPosition().x + nodeRadius,
                 _selectedNode->GetShape().getPosition().y + nodeRadius));
      ImGui::SetNextWindowSize(ImVec2(400, 350));
      ImGui::Begin("Node Info", nullptr,
                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                       ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                       ImGuiWindowFlags_NoScrollWithMouse |
                       ImGuiWindowFlags_NoCollapse);
      ImGui::Text("Node %s", _selectedNode->content.c_str());
      // input text for the node content that updates the node content
      static char buffer[256];
      if (ImGui::InputText("Content", buffer, 256)) {
        _selectedNode->content = buffer;
      }

      // parent
      ImGui::PushID("Parent");
      if (ImGui::Button("Parent",
                        ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
        _selectedNode = _selectedNode->parent;
      }
      ImGui::PopID();

      // siblings
      ImGui::Text("Childrens: ");
      ImGui::SameLine();
      // button that select the sibling
      if (_selectedNode->left) {
        ImGui::PushID(_selectedNode->left->content.c_str());
        if (ImGui::Button(_selectedNode->left->content.c_str())) {
          _selectedNode = _selectedNode->left;
        }
        ImGui::PopID();
      }

      ImGui::SameLine();
      if (_selectedNode->right) {
        ImGui::PushID(_selectedNode->right->content.c_str());
        if (ImGui::Button(_selectedNode->right->content.c_str())) {
          _selectedNode = _selectedNode->right;
        }
        ImGui::PopID();
      }

      // two buttons to rotate the tree left and right
      ImGui::PushID("Rotate Left");
      if (ImGui::Button("Rotate Left",
                        ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
        _selectedNode->RotateLeft();
      }
      ImGui::PopID();

      ImGui::PushID("Rotate Right");
      if (ImGui::Button("Rotate Right",
                        ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
        _selectedNode->RotateRight();
      }
      ImGui::PopID();

      // draw the path from the root to the current node
      std::shared_ptr<TreeNode> node = _selectedNode;
      while (node) {
        node->GetShape().setOutlineThickness(2);
        node->GetShape().setFillColor(sf::Color::Green);

        node = node->parent;
      }

      ImGui::End();
    }

    rt.clear(sf::Color(33, 33, 33));

    if (_root)
      _root->Render(rt, {treePos.x, treePos.y}, _root->GetHeight(), 0,
                    {nodeMargin.x, nodeMargin.y}, nodeRadius, &_font);

    ImGui::Image(rt);
  }
  ImGui::End();
  ImGui::PopStyleVar();

  if (ImGui::Begin("Tree Settings")) {

    ImGui::SliderInt("Size", (int *)&nodeSize, 1, 100);
    ImGui::SliderFloat2("Margin", (float *)&nodeMargin, 1, 200);
    ImGui::SliderFloat("Radius", &nodeRadius, 1, 100);
    ImGui::SliderInt("Width", (int *)&treeWidth, 1, 1000);
    ImGui::SliderFloat2("Position", (float *)&treePos, 0, viewportSize.x);
  }
  ImGui::End();

  if (ImGui::Begin("Node Settings")) {
    // print all the values of the _nodes vector
    for (auto &node : _nodes) {
      // filled width button
      ImGui::PushID(node->content.c_str());
      if (ImGui::Button((node->content).c_str(),
                        ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
        _selectedNode = node;
      }
      ImGui::PopID();
    }
  }
  ImGui::End();

  ImGui::PopFont();

  SFMLRender();
}

void Window::SFMLRender() {
  _window->clear();
  _window->draw(_shape);
  ImGui::SFML::Render(*_window);
  _window->display();
}

} // namespace TreeVisualizer
