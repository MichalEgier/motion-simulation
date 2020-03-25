#define boolean int
#define true 1
#define false 0

struct NodeValue{

	boolean isOperator;

	int precendence;

	char operator;

	int value;

}

struct Node{

	struct NodeValue* value;

	struct Node *leftChild;

	struct Node *rightChild;

	struct Node *parent;

}

void moveNodeUp(struct Node * belowNode, struct Node * upperNode){

	struct Node * parent_of_upper = upperNode -> parent;
	
	struct Node * second_child_of_upper;

	if(upperNode->leftChild == belowNode) {

		second_child_of_upper = upperNode -> rightChild;
	
		if(second_child_of_upper != NULL){

			second_child_of_upper -> parent = belowNode;				
		}	

		

	}
	else second_child_of_upper = upperNode -> leftChild

	

} 
