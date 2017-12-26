#include "DialogueTree.h"

/**
	Default constructor; does not do anything.
 */
DialogueTree::DialogueTree() { }

/**
	Destructor, called when the object instance is destroyed.
 */
DialogueTree::~DialogueTree()
{
	this->removeAllDialogueNodes();
} //end destructor

/**
	Returns a reference to this instance's vector of DialogueNode pointers.

	@return A vector of DialogueNode pointers.
 */
std::vector<DialogueNode*>& DialogueTree::getDialogueNodes()
{
	return this->nodes;
} //end getDialogueNodes

/**
	Retrieves the first DialogueNode in this instance.

	@return A pointer to the first DialogueNode in the tree if the tree contains any,
	otherwise nullptr.
 */
DialogueNode* DialogueTree::getFirstNode() const
{
	return this->nodes.size() > 0 ? this->nodes.at(0) : nullptr;
} //end getFirstNode

/**
	Searches for a DialogueNode with a specific ID and retrieves it.

	@param nodeID  The ID of the DialogueNode being requested.
	@return A DialogueNode pointer if the specified one is found, otherwise nullptr.
 */
DialogueNode* DialogueTree::getDialogueNodeWithID(unsigned int nodeID) const
{
	for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it)
		if ((*it)->getID() == nodeID) //check if the IDs match
			return *it;

	return nullptr; //the ID wasn't found
} //end getDialoguesNodeWithID

/**
	Checks the amount of DialogueNodes in this instance and returns the amount.

	@return An int representing the number of DialogueNodes in the tree.
 */
int DialogueTree::getNumNodes() const
{
	return this->nodes.size();
} //end getNumNodes

/**
	Appends an empty DialogueNode to the tree.

	@param nodeID  The ID of the new DialogueNode.
	@param nodeText  The text assigned to the DialogueNode.
 */
void DialogueTree::addDialogueNode(unsigned int nodeID, std::string nodeText)
{
	DialogueNode* newNode = new DialogueNode(nodeID, nodeText);
	this->nodes.push_back(newNode);
} //end addDialogueNode

/**
	Removes a DialogueNode from the tree and frees the memory allocated to that node.
	Additionally, any DialogueOptions pointing to the specified DialogueNode will be
	set to point to nullptr.

	@param nodeID  The ID of the DialogueNode to be removed.
 */
void DialogueTree::removeDialogueNode(unsigned int nodeID)
{
	for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{
		if ((*it)->getID() == nodeID) //check if the IDs match
		{
			// Remove the node from the tree
			DialogueNode* tmp = *it;
			this->nodes.erase(it);
			tmp->removeAllDialogueOptions();
			
			// Remove references to the removed node from all other nodes
			for (auto i = this->nodes.begin(); i != this->nodes.end(); ++i)
				for (auto j = (*i)->getOptions().begin(); j != (*i)->getOptions().end(); ++j)
					if ((*j)->nextNode == tmp)
						(*j)->nextNode = nullptr;
	
			// Free memory and finish
			delete tmp;
			break;
		} //end if
	} //end for
} //end removeDialogueNode

/**
	Removes and frees the memory allocated to each DialogueNode in the tree.
 */
void DialogueTree::removeAllDialogueNodes()
{
	while (this->nodes.size() > 0)
		removeDialogueNode(this->nodes.at(0)->getID());
} //end removeAllDialogueNodes