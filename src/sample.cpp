#include "DialogueTree.h"
#include <iostream>
 
int main()
{
	/// The DialogueTree instance itself requires no parameters.
	DialogueTree tree;

	/// Add the DialogueNodes to the tree. Any positive integer can be used as an ID for a
	/// DialogueNode; the ones used here are kept simple for example purposes.
	///
	///	NOTE:	Dialogue should really be read in from a file, and not manually emplaced in code.
	///			This DialogueTree is filled manually here for example purposes, but in reality
	///			this structure would be filled after parsing another file containing the data
	///			itself, such as an XML document.
	tree.addDialogueNode(1, "This is test node 1.");
	tree.addDialogueNode(2, "This is test node 2.");
	tree.addDialogueNode(3, "This is test node 3.");

	/// Add DialogueOptions to each DialogueNode. DialogueOptions can point to another
	/// DialogueNode or to nullptr (which would indicate the dialogue has ended).
	tree.getDialogueNodeWithID(1)->addDialogueOption("An option from node 1. Select this to go to node 2.", tree.getDialogueNodeWithID(2));
	tree.getDialogueNodeWithID(1)->addDialogueOption("An option from node 1. Select this to go to node 3.", tree.getDialogueNodeWithID(3));
	tree.getDialogueNodeWithID(1)->addDialogueOption("An option from node 1. Select this to exit.", nullptr);

	tree.getDialogueNodeWithID(2)->addDialogueOption("An option from node 2. Select this to go to node 1.", tree.getDialogueNodeWithID(1));
	tree.getDialogueNodeWithID(2)->addDialogueOption("An option from node 2. Select this to go to node 3.", tree.getDialogueNodeWithID(3));
	tree.getDialogueNodeWithID(2)->addDialogueOption("An option from node 2. Select this to exit.", nullptr);

	tree.getDialogueNodeWithID(3)->addDialogueOption("An option from node 3. Select this to go to node 1.", tree.getDialogueNodeWithID(1));
	tree.getDialogueNodeWithID(3)->addDialogueOption("An option from node 3. Select this to go to node 2.", tree.getDialogueNodeWithID(2));
	tree.getDialogueNodeWithID(3)->addDialogueOption("An option from node 3. Select this to exit.", nullptr);

	/// Note that we can supply an optional integer argument to serve as a flag
	/// associated with selecting this option. This argument will default to 0, which
	/// indicates nothing additional for selecting this option, but any integer can be
	/// supplied and later used for additional processing. An example of this will be
	/// implemented in this program.
	tree.getDialogueNodeWithID(3)->addDialogueOption("Select this to go to node 1 and remove node 3 from the tree.", tree.getDialogueNodeWithID(1), 1);

	/// Create a DialogueNode to serve as the node being viewed currently. In most cases
	/// this will start at the first DialogueNode in the tree, but any DialogueNode can
	/// be supplied.
	DialogueNode* currentNode = tree.getFirstNode();

	/// Following a user input, currentNode will be set to the DialogueNode pointed to by
	/// the DialogueOption the user selected. If the selected DialogueOption is the end of
	/// the conversation, currentNode will be set to nullptr and this loop, which takes the
	/// user's input, will terminate.
	while (currentNode != nullptr)
	{
		//printouts to show the current node's composition
		std::cout << "Node #" << currentNode->getID() << ": " << currentNode->getText() << "\n";
		for (int i = 0; i < currentNode->getNumOptions(); ++i)
			std::cout << "\t[" << i+1 << "] " << currentNode->getOptions().at(i)->optionText << "\n";

		//input is numerical; 1 is subtracted from input because vectors are 0-indexed
		int input;
		std::cin >> input;
		--input;

		/// Note that from this point onward, there are a myriad of implementations and applications
		/// of a DialogueTree and its components, and this example is but a specific case that will
		/// hopefully showcase some of the capabilities of the DialogueTree (as well as some of the
		/// steps that need to be taken for risk management).

		//input outside the range of options is ignored
		if (input < currentNode->getNumOptions() && input >= 0)
		{
			/// Here, we make use of the optional integer argument of a DialogueOption. In this example,
			/// we want to remove a DialogueNode from the DialogueTree if a certain option is selected.
			/// First, we check if the selected DialogueOption has a specific value (i.e. one that is not
			/// equal to 0). If it does...
			if (currentNode->getOptions().at(input)->optionVal == 1)
			{
				/// ...then we proceed to remove the DialogueNode. We hold on to the DialogueNode with a
				/// temporary pointer, and move currentNode to the next specified DialogueNode. We don't
				/// remove the DialogueNode quite yet, as we will use it in the next step.
				DialogueNode* tmp = currentNode;
				currentNode = currentNode->getOptions().at(input)->nextNode;

				/// At this point, we could simple remove the DialogueNode. However, if we did, some of
				/// the remaining DialogueOptions in other DialogueNodes might still be trying to point
				/// to the DialogueNode we just removed, and selecting one of those DialogueOptions would
				/// cause the program to crash. To fix this, we must locate those DialogueOptions and set
				/// their DialogueNode pointers to point to something else. We could potentially set them
				/// to point to another DialogueNode, but in this example we will just set them to nullptr.
				///
				/// This behavior is not automatically handled in DialogueTree::removeDialogueNode() because
				/// the aftermath of removing DialogueNodes may vary based on the design of your program.
				for (auto it = tree.getDialogueNodes().begin(); it != tree.getDialogueNodes().end(); ++it) //iterate through each DialogueNode
				{
					/// Since the DialogueNode we want to remove is still in the vector of DialogueNodes,
					/// we check to make sure we ignore the one we want to remove.
					if ((*it)->getID() != tmp->getID())
					{
						/// We must check every single DialogueOption in this DialogueNode.
						for (int i = 0; i < (*it)->getOptions().size(); ++i)
						{
							/// We check which DialogueOptions point to the DialogueNode we just removed.
							/// There are many ways to do this depending on your implementation, but in
							/// this example we simply compare each DialogueOption's nextNode field with
							/// the DialogueNode we are removing to see if they match. If they do...
							if ((*it)->getOptions().at(i)->nextNode == tmp)
							{
								/// ...we remove that DialogueOption.
								tree.getDialogueNodeWithID((*it)->getID())->removeDialogueOption(i);

								/// We could simply leave this DialogueNode with one less DialogueOption,
								/// and there would be no issues. To show that DialogueOptions are easily
								/// replaceable, we will add a new one to take place of the previous one.
								tree.getDialogueNodeWithID((*it)->getID())->addDialogueOption("A new option! Select this to exit.", nullptr);
							} //end if
						} //end for
					} //end if
				} //end for

				/// Now that we have changed the pointers for any DialogueOptions pointing to this
				/// DialogueNode, we can finally remove it.
				/// It is possible to remove it before adjusting the remaining DialogueOptions, but
				/// this makes searching for DialogueOptions linked to this DialogueNode more tedious.
				tree.removeDialogueNode(tmp->getID());
			} //end if
			else
			{
				/// If the optional integer argument doesn't match any of the specific ones we are
				/// looking for, we simply move to the next specified DialogueNode.
				currentNode = currentNode->getOptions().at(input)->nextNode;
			} //end else
		} //end if

		std::cout << "\n";
	} //end while

	/// Once currentNode reaches a nullptr, the loop terminates and the program exits.
	return 0;
} //end main
