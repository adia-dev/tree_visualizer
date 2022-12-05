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
		TreeNode();
		TreeNode(const std::string &content);
		TreeNode(const std::string &content, std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right);

		~TreeNode()
		{
			std::cout << "Deleting node: " << content << "\n";
		}

		static std::shared_ptr<TreeNode> FromVector(const std::vector<std::string> &vec);
		static std::shared_ptr<TreeNode> CombinaisonTree(const std::string &word);

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

		std::shared_ptr<TreeNode> RotateLeft();
		std::shared_ptr<TreeNode> RotateRight();

		void Update(const sf::Vector2f &mousePos);
		void Render(sf::RenderTarget &target, sf::Vector2f pos, int height, int depth, sf::Vector2f margin, float radius, sf::Font *font = nullptr);

		std::string content;
		std::shared_ptr<TreeNode> left = nullptr;
		std::shared_ptr<TreeNode> right = nullptr;
		std::shared_ptr<TreeNode> parent = nullptr;

		sf::Text text;
		sf::CircleShape shape;
	};
} // TreeVisualizer
