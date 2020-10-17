#pragma once
#include <vector>
#include <memory>

template<typename T>
class Node
{
private:
	T Value;
	int Height;
	static int ChooseRandomHeight(int MaxHeight);
public:
	std::vector<std::shared_ptr<Node<T>>> NextNodes;
	Node(T Value, int MaxHeight);
	static std::shared_ptr<Node<T>> Create(T Value, int MaxHeight);
	T GetValue() const;
	void SetValue(T newValue);
	int GetHeight() const;
	void SetHeight(int newHeight);
};

template<typename T>
Node<T>::Node(T value, int MaxHeight)
{
	Value = value;
	Height = ChooseRandomHeight(MaxHeight);
	NextNodes = std::vector<std::shared_ptr<Node<T>>>();
	for (int i = 0; i < Height; i++) NextNodes.push_back(nullptr);
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::Create(T Value, int MaxHeight)
{
	return std::make_shared<Node<T>>(Value, MaxHeight);
}

template<typename T>
int Node<T>::ChooseRandomHeight(int MaxHeight)
{
	int Height = 0;
	bool isHeads = true;
	do
	{
		Height++;
		isHeads = rand() % 2 == 0;
	} while (isHeads && Height < MaxHeight);
	return Height;
}

template<typename T>
int Node<T>::GetHeight() const
{
	return Height;
}

template<typename T>
T Node<T>::GetValue() const
{
	return Value;
}

template<typename T>
void Node<T>::SetHeight(int newHeight)
{
	Height = newHeight;
}

template<typename T>
void Node<T>::SetValue(T newValue)
{
	Value = newValue;
}