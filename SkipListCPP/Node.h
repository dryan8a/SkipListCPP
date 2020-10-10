#pragma once
#include <memory>
#include <vector>

template<typename T>
class Node
{
private:
	T Value;
	int Height;
	int ChooseRandomHeight(int MaxHeight) const;
public:
	std::vector<Node<T>> NextNodes;
	Node(T Value, int MaxHeight);
	static std::shared_ptr<Node<T>> Create(T Value, int MaxHeight);
	T GetValue();
	void SetValue(T newValue);
	int GetHeight();
	void SetHeight(int newHeight);
};

template<typename T>
Node<T>::Node(T Value, int MaxHeight)
{
	this.Value = Value;
	Height = ChooseRandomHeight(MaxHeight);
}

template<typename T>
static std::shared_ptr<Node<T>> Node<T>::Create(T Value, int MaxHeight)
{
	return std::make_shared<Node<T>>(Value, MaxHeight);
}

