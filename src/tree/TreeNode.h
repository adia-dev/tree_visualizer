//
// Created by abdoulayedia on 04.12.2022
//
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <stack>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

namespace TreeVisualizer
{
	// TreeNode
	struct TreeNode : public std::enable_shared_from_this<TreeNode>
	{

		TreeNode()
			: content(""), left(nullptr), right(nullptr), parent(nullptr)
		{
			shape.setOutlineColor(sf::Color::Black);
			shape.setOutlineThickness(2);
		}

		TreeNode(const std::string &content)
			: content(content), left(nullptr), right(nullptr), parent(nullptr)
		{
			shape.setOutlineColor(sf::Color::Black);
			shape.setOutlineThickness(2);
		}

		~TreeNode()
		{
			std::cout << "Deleting node: " << content << "\n";
		}

		static std::shared_ptr<TreeNode> FromVector(const std::vector<std::string> &vec)
		{
			std::shared_ptr<TreeNode> root = std::make_shared<TreeNode>(vec[0]);
			std::queue<std::shared_ptr<TreeNode>> q;
			q.push(root);

			for (int i = 1; i < vec.size(); i += 2)
			{
				std::shared_ptr<TreeNode> node = q.front();
				q.pop();

				if (vec[i] != "")
				{
					node->left = std::make_shared<TreeNode>(vec[i]);
					node->left->parent = node;
					q.push(node->left);
				}

				if (i + 1 < vec.size() && vec[i + 1] != "")
				{
					node->right = std::make_shared<TreeNode>(vec[i + 1]);
					node->right->parent = node;
					q.push(node->right);
				}
			}

			return root;
		}

		static std::shared_ptr<TreeNode> CombinaisonTree(const std::string &word)
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

		uint16_t GetHeight() const
		{
			uint16_t leftHeight = left ? left->GetHeight() : 0;
			uint16_t rightHeight = right ? right->GetHeight() : 0;

			return std::max(leftHeight, rightHeight) + 1;
		}

		sf::Shape &GetShape()
		{
			return shape;
		}

		bool IsLeaf() const
		{
			return !left && !right;
		}

		std::shared_ptr<TreeNode> RotateLeft()
		{
			std::shared_ptr<TreeNode> newRoot = right;
			std::shared_ptr<TreeNode> newLeft = newRoot->left;

			newRoot->left = shared_from_this();
			newRoot->parent = parent;

			right = newLeft;
			if (newLeft)
				newLeft->parent = shared_from_this();

			parent = newRoot;

			return newRoot;
		}

		std::shared_ptr<TreeNode> RotateRight()
		{
			std::shared_ptr<TreeNode> newRoot = left;
			std::shared_ptr<TreeNode> newRight = newRoot->right;

			newRoot->right = shared_from_this();
			newRoot->parent = parent;

			left = newRight;
			if (newRight)
				newRight->parent = shared_from_this();

			parent = newRoot;

			return newRoot;
		}

		void Update(sf::Vector2f mousePos)
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

		void Render(sf::RenderTarget &target, sf::Vector2f pos, int height, int depth, sf::Vector2f margin, float radius, sf::Font *font = nullptr)
		{

			uint16_t width = (uint16_t)(std::pow(2, (height + 1) / 2) * margin.x);

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

				left->Render(target, leftPos, height - 1, depth + 1, margin, radius, font);
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

				right->Render(target, rightPos, height - 1, depth + 1, margin, radius, font);
			}
			// the radius is calculated based on the content of the node, it is a string
			shape.setRadius(radius + content.length() * 2);
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

		std::string content;
		std::shared_ptr<TreeNode> left = nullptr;
		std::shared_ptr<TreeNode> right = nullptr;
		std::shared_ptr<TreeNode> parent = nullptr;

		sf::Text text;
		sf::CircleShape shape;
	};
} // TreeVisualizer
