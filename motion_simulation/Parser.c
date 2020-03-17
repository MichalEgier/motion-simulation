#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

double parse_and_evaluate_expression(const char* expression,double v_x,double v_y,double v_z,double r_x,double r_y,double r_z,double t);

enum NodeID
{
	OPENBRACKET,
	CLOSEBRACKET,

	POSITIVE,
	NEGATIVE,

	PLUS,
	MINUS,
	TIMES,
	DIVIDE,

	EXPONENT,
	FACTORIAL,

	SIN,
	COS,
	TAN,

	NUMBER
};

enum NodeInfo
{
	NoInfo,
	SkipClimbUp,
	RightAssociative
};

typedef struct _Node {
	enum NodeID ID;
	int pre; /* precedence */
	double number;
} Node;


double factorial (double n)
{
	long i, ans=1, m=(long)n;
	for(i=1; i<=m; i++) ans *= i;
	return (double)ans;
}

Node* insert_node_item (Node* current, Node item, enum NodeInfo info)
{
	double left, right;
	if(info == SkipClimbUp) current+=1;
	else
	{
		while(1)
		{
			if(info == RightAssociative)
			     { if(current->pre <= item.pre) break; }
			else { if(current->pre <  item.pre) break; }

			left  = (current-1)->number;
			right = (current+1)->number;
			switch(current->ID)
			{
			case POSITIVE:  (  current)->number = +right; break;
			case NEGATIVE:  (  current)->number = -right; break;
			case PLUS:      (--current)->number = left + right; break;
			case MINUS:     (--current)->number = left - right; break;
			case TIMES:     (--current)->number = left * right; break;
			case DIVIDE:    (--current)->number = left / right; break;
			case EXPONENT:  (--current)->number = pow(left, right); break;
			case FACTORIAL: (--current)->number = factorial(left); break;
			case SIN:       (  current)->number = sin(right); break;
			case COS:       (  current)->number = cos(right); break;
			case TAN:       (  current)->number = tan(right); break;
			default:        break;
			}
			current->ID = NUMBER; /* force node to be a number */
			current->pre = 10;    /* set to highest precedence */
			current--;  /* prepare for next iteration */
		}
		switch(item.ID)
		{
			case CLOSEBRACKET:
				*current = *(current+1);
				/* current-=1; this part is optional */
				break;
			case PLUS:
			case MINUS:
			case TIMES:
			case DIVIDE:
			case EXPONENT:
			case FACTORIAL: current+=2; break;
			default:        current+=1; break;
		}
	}
	if(item.ID != CLOSEBRACKET)
		*current = item;
	return current;
}


void print_stack_array (const Node* node, const Node* stop)
{
	char number[20];
	const char* str;
	if(!node) return;

	for( ; node <= stop; node++)
	{
		switch(node->ID) /* prepare to print current node */
		{
			case NUMBER:
				if((long)node->number == node->number)
				     sprintf(number, "%.0f", node->number);
				else sprintf(number, "%.2f", node->number);
				str = number;
				break;
			case OPENBRACKET: str = "(";   break;
			case POSITIVE:    str = "+ve"; break;
			case NEGATIVE:    str = "-ve"; break;
			case PLUS:        str = "+";   break;
			case MINUS:       str = "-";   break;
			case TIMES:       str = "*";   break;
			case DIVIDE:      str = "/";   break;
			case EXPONENT:    str = "^";   break;
			case FACTORIAL:   str = "!";   break;
			case SIN:         str = "sin"; break;
			case COS:         str = "cos"; break;
			case TAN:         str = "tan"; break;
			default:          str = "error";
		}
		printf(" %s", str);
	}
	printf("\n");
}


double parse_and_evaluate_expression(const char* expression,double v_x,double v_y,double v_z,double r_x,double r_y,double r_z,double t)
{
	int i;
	char c;
	char number[20];
	enum NodeInfo info;
	enum NodeID previousID;
	Node node, *current;
	Node stack[1000];

	if(expression==NULL) return 0;

	/* Initialise the stack with the '(' node */
	stack[0].pre = 1;
	stack[0].ID = OPENBRACKET;
	previousID = OPENBRACKET;
	current = stack; /* stack[0] is the root node */

	/* Do the expression parse and evaluate */
	while(1)
	{
		info = NoInfo; /* set info to default value */
		node.pre = 10; /* assume precedence is highest */

		c = *expression++; /* get latest character of string */

		if(c=='\0') break;  /* if at the end of input string */

		else if(c==' ' || c=='\t' || c=='\r' || c=='\n') continue;

		else if(c=='(') { node.ID = OPENBRACKET;  node.pre = 1; info = SkipClimbUp; }
		else if(c==')') { node.ID = CLOSEBRACKET; node.pre = 1; info = RightAssociative; }

		else if(c=='+')
		{
			if(previousID == NUMBER
			|| previousID == FACTORIAL
			|| previousID == CLOSEBRACKET)
			     { node.ID = PLUS; node.pre = 2; }
			else { node.ID = POSITIVE; node.pre = 3; info = SkipClimbUp; }
		}
		else if(c=='-')
		{
			if(previousID == NUMBER
			|| previousID == FACTORIAL
			|| previousID == CLOSEBRACKET)
			     { node.ID = MINUS; node.pre = 2; }
			else { node.ID = NEGATIVE; node.pre = 3; info = SkipClimbUp; }
		}

		else if(c=='*') { node.ID = TIMES; node.pre = 4; }
		else if(c=='/') { node.ID = DIVIDE; node.pre = 4; }
		else if(c=='^') { node.ID = EXPONENT; node.pre = 5; info = RightAssociative; }
		else if(c=='!') { node.ID = FACTORIAL; node.pre = 6; }

		else if(0==memcmp(expression-1, "sin", 3)) { expression += 3-1; node.ID = SIN; }
		else if(0==memcmp(expression-1, "cos", 3)) { expression += 3-1; node.ID = COS; }
		else if(0==memcmp(expression-1, "tan", 3)) { expression += 3-1; node.ID = TAN; }

		else if(0==memcmp(expression-1, "pi", 2))
		{
			expression += 2-1;
			node.number = 3.141592653;
			node.ID = NUMBER;
		}
		else if('0'<=c && c<='9')   /* if next item is a number */
		{
			i=0;
			while(1)
			{
				number[i++] = c;
				if(i+1==sizeof(number)) break;
				c = *expression;
				if(('0'<=c && c<='9') || c=='.')
					expression++;
				else break;
			}
			number[i] = '\0';
			sscanf(number, "%lf", &node.number);
			node.ID = NUMBER;
		}
		
		else if(c == 't' || c == 'T'){

			node.ID = NUMBER;

			node.number = t;

		}

		else if(c == 'v' || c == 'V'){

			node.ID = NUMBER;

				//expression not incremented here, because it is postincremented at the beginning of while loop
			if(*expression == 'z' || *expression == 'Z'){

				node.number = v_z;			

			}

			else if(*expression == 'x' || *expression == 'X'){

				node.number = v_x;	

			}

			else if(*expression == 'y' || *expression == 'Y'){

				node.number = v_y;	

			}

			expression++;

		} 

		else if(c == 'r' || c == 'R'){

			node.ID = NUMBER;

			if(*expression == 'z' || *expression == 'Z'){

				node.number = r_z;			

			}

			else if(*expression == 'x' || *expression == 'X'){

				node.number = r_x;	

			}

			else if(*expression == 'y' || *expression == 'Y'){

				node.number = r_y;	

			}

			expression++;		

		}

		else /* if a parsing error */
		{
			printf("Unrecognised character '%c'.\n", c);
			return 0;
		}

		previousID = node.ID; /* prepare for next iteration */

		current = insert_node_item (current, node, info);

//		print_stack_array (stack, current);
	}

	/* Finalise the algorithm with an ')' node */
	{ node.ID = CLOSEBRACKET; node.pre = 1; info = RightAssociative; }
	current = insert_node_item (current, node, info);

	assert(current==stack); /* make a final error check */
	return stack[0].number; /* return result */
}

