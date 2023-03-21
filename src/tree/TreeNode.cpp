#include "TreeNode.h"

namespace TreeVisualizer
{
    TreeNode::TreeNode()
        : content(""), left(nullptr), right(nullptr), parent(nullptr)
    {
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);
    }

    TreeNode::TreeNode(const std::string &content)
        : content(content), left(nullptr), right(nullptr), parent(nullptr)
    {
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);
    }

    TreeNode::TreeNode(const std::string &content, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right)
        : content(content), left(left), right(right), parent(nullptr)
    {
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);
    }

    std::shared_ptr<TreeNode> TreeNode::FromVector(const std::vector<std::string> &vec)
    {
        std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(vec[0]);
        // to avoid the shared_ptr not being deleted properly, use a queue of weak_ptr instead, add the content of the queue to the tree, and then clear the queue
        std::queue<std::weak_ptr<TreeNode>> queue;
        queue.push(root);
        for (int i = 1; i < vec.size(); i += 2)
        {
            std::shared_ptr<TreeNode> node = queue.front().lock();
            // print the reference count of the shared_ptr
            queue.pop();
            if (vec[i] != "")
            {
                node->left = std::make_shared<TreeNode>(vec[i]);
                node->left->parent = node;
                queue.push(node->left);
            }
            if (i + 1 < vec.size() && vec[i + 1] != "")
            {
                node->right = std::make_shared<TreeNode>(vec[i + 1]);
                node->right->parent = node;
                queue.push(node->right);
            }
        }

        return root;
    }

    std::shared_ptr<TreeNode> TreeNode::CombinaisonTree(const std::string &word)
    {
        // use backtracking to generate all possible trees

        std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(word);
        std::queue<std::shared_ptr<TreeNode>> q;
        q.push(root);

        while (!q.empty())
        {
            std::shared_ptr<TreeNode> node = q.front();
            q.pop();

            if (node->content.size() > 1)
            {
                for (int i = 1; i < node->content.size(); i++)
                {
                    std::string left = node->content.substr(0, i);
                    std::string right = node->content.substr(i, node->content.size() - i);

                    std::shared_ptr<TreeNode> leftNode = std::make_shared<TreeNode>(left);
                    std::shared_ptr<TreeNode> rightNode = std::make_shared<TreeNode>(right);

                    node->left = leftNode;
                    node->right = rightNode;

                    leftNode->parent = node;
                    rightNode->parent = node;

                    q.push(leftNode);
                    q.push(rightNode);
                }
            }
        }

        return root;
    }

    std::vector<std::string> TreeNode::WordCombinations(std::string str, std::vector<std::string> vec)
    {
        if (str.size() == 0)
        {
            return vec;
        }
        std::vector<std::string> newVec;
        for (auto s : vec)
        {
            newVec.push_back(s + str[0]);
            newVec.push_back(s);
        }
        str.erase(0, 1);
        return WordCombinations(str, newVec);
    }

    std::vector<std::string> TreeNode::WordCombinations(std::string str)
    {
        static std::vector<std::string> vec = {""};

        if (str.size() == 0)
        {
            return vec;
        }
        std::vector<std::string> newVec;
        for (auto s : vec)
        {
            newVec.push_back(s + str[0]);
            newVec.push_back(s);
        }
        str.erase(0, 1);
        return WordCombinations(str, newVec);
    }

    std::shared_ptr<TreeNode> TreeNode::RotateLeft()
    {
        return nullptr;
    }

    std::shared_ptr<TreeNode> TreeNode::RotateRight()
    {
        return nullptr;
    }

    void TreeNode::Update(const sf::Vector2f &mousePos)
    {

        if (shape.getGlobalBounds().contains(mousePos))
        {
            shape.setFillColor(sf::Color::Red);
            // set the color of all the parent to red as well
            std::shared_ptr<TreeNode> parent = this->parent;
            while (parent)
            {
                parent->shape.setFillColor(sf::Color::Red);
                parent = parent->parent;
            }
        }
        else
        {
            shape.setFillColor(sf::Color::White);
        }
    }

    void TreeNode::Render(sf::RenderTarget &target, sf::Vector2f pos, int height, int depth, sf::Vector2f margin, float radius, sf::Font *font)
    {

        uint16_t width = (uint16_t)(std::pow(4, (height + 1) / 2) * margin.x * 2);
        // calculate the radius so that the circle fits in the margin
        Render(target, pos, width, height, depth, margin, radius, font);
    }

    void TreeNode::Render(sf::RenderTarget &target, sf::Vector2f pos, int width, int height, int depth, sf::Vector2f margin, float radius, sf::Font *font)
    {
        if (left != nullptr)
        {
            sf::Vector2f leftPos = pos;
            leftPos.x -= margin.x + width;
            leftPos.y += margin.y;

            sf::Vertex line[] =
                {
                    sf::Vertex(pos),
                    sf::Vertex(leftPos)};

            target.draw(line, 2, sf::Lines);

            left->Render(target, leftPos, width / 2, height, depth + 1, margin, radius, font);
        }

        if (right != nullptr)
        {
            sf::Vector2f rightPos = pos;
            rightPos.x += margin.x + width;
            rightPos.y += margin.y;

            sf::Vertex line[] =
                {
                    sf::Vertex(pos),
                    sf::Vertex(rightPos)};

            target.draw(line, 2, sf::Lines);

            right->Render(target, rightPos, width / 2, height, depth + 1, margin, radius, font);
        }
        // the radius is calculated based on the content of the node, it is a string
        shape.setRadius(radius + content.length() * 4);
        shape.setPosition(pos);
        shape.setOrigin(radius, radius);

        target.draw(shape);

        if (font)
        {
            text.setFont(*font);
            text.setString(content);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);
            text.setOrigin(this->content.length() * 5, 10);
            text.setPosition(pos);
            target.draw(text);
        }
    }
}