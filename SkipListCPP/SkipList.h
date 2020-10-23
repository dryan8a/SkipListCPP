#pragma once
#include "Node.h"

template<typename T>
class SkipList
{
private:
	std::shared_ptr<Node<T>> Head;
	void IncreaseMaxHeight();
public:
	SkipList(int maxHeight = 5);
	static std::unique_ptr<SkipList<T>> Create(int maxHeight = 5);
	bool Insert(T value);
	bool Remove(T value);
	std::shared_ptr<Node<T>> Find(T value) const;
	bool Contains(T value) const;
	std::shared_ptr<Node<T>> GetHead() const;
	int GetMaxHeight() const;
};

template<typename T>
SkipList<T>::SkipList(int maxHeight)
{
	Head = Node<T>::Create(NULL, maxHeight);
}

template<typename T>
std::unique_ptr<SkipList<T>> SkipList<T>::Create(int maxHeight)
{
	return std::make_unique<SkipList<T>>(maxHeight);
}

template<typename T>
std::shared_ptr<Node<T>> SkipList<T>::GetHead() const
{
	return Head;
}

template<typename T>
int SkipList<T>::GetMaxHeight() const
{
	return Head->GetHeight();
}

template<typename T>
void SkipList<T>::IncreaseMaxHeight()
{
	Head->SetHeight(Head->GetHeight() + 1);
	Head->NextNodes.push_back(nullptr);
}

template<typename T>
std::shared_ptr<Node<T>> SkipList<T>::Find(T value) const
{
	auto currentNode = Head;
	for (int i = currentNode->GetHeight()-1; i >= 0 ; i--)
	{
		if (currentNode->NextNodes[i] == nullptr || currentNode->NextNodes[i]->GetValue() > value) continue;
		if (currentNode->NextNodes[i]->GetValue() < value)
		{
			currentNode = currentNode->NextNodes[i];
			i = currentNode->GetHeight();
			continue;
		}
		return currentNode->NextNodes[i];
	}
	return nullptr;
}

template<typename T>
bool SkipList<T>::Contains(T value) const
{
	auto currentNode = Head;
	for (int i = currentNode->GetHeight() - 1; i >= 0; i--)
	{
		if (currentNode->NextNodes[i] == nullptr || currentNode->NextNodes[i]->GetValue() > value) continue;
		if (currentNode->NextNodes[i]->GetValue() < value)
		{
			currentNode = currentNode->NextNodes[i];
			i = currentNode->GetHeight();
			continue;
		}
		return true;
	}
	return false;
}

template<typename T>
bool SkipList<T>::Insert(T value)
{
	auto newNode = Node<T>::Create(value, GetMaxHeight() + 1);
	if (newNode->GetHeight() > GetMaxHeight()) IncreaseMaxHeight();
	auto currentNode = Head;
	for (int i = currentNode->GetHeight() - 1; i >= 0; i--)
	{
		if (currentNode->NextNodes[i] == nullptr || currentNode->NextNodes[i]->GetValue() > value)
		{
			if (i < newNode->GetHeight())
			{
				newNode->NextNodes[i] = currentNode->NextNodes[i];
				currentNode->NextNodes[i] = newNode;
			}
			continue;
		}
		if (currentNode->NextNodes[i]->GetValue() < value)
		{
			currentNode = currentNode->NextNodes[i];
			i = currentNode->GetHeight();
			continue;
		}
		return false;
	}
	return true;
}

template<typename T>
bool SkipList<T>::Remove(T value)
{
	bool didFind = false;
	auto currentNode = Head;
	for (int i = currentNode->GetHeight() - 1; i >= 0; i--)
	{
		if (currentNode->NextNodes[i] == nullptr || currentNode->NextNodes[i]->GetValue() >= value)
		{
			if (currentNode->NextNodes[i] != nullptr && currentNode->NextNodes[i]->GetValue() == value)
			{
				currentNode->NextNodes[i] = currentNode->NextNodes[i]->NextNodes[i];
				didFind = true;
			}
			continue;
		}
		currentNode = currentNode->NextNodes[i];
		i = currentNode->GetHeight();
		continue;
	}
	return didFind;
}