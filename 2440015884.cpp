#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Node{
	char id[50];
	char productName[50];
	char productType[50];
	char productStatus[50];
	char description[100];
	int productPrice;
	int height;
	Node* left;
	Node* right;
}*root = NULL;

Node* createNode(char id[],char productName[],char productType[],char productStatus[50],
				char description[],int productPrice,int productStock){
	
	Node* newNode = (Node*) malloc(sizeof(Node));
	strcpy(newNode->id, id);
	strcpy(newNode->productName, productName);
	strcpy(newNode->productType, productType);
	strcpy(newNode->productStatus, productStatus);
	strcpy(newNode->description, description);
	newNode->productPrice = productPrice;
	
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int max(int a, int b) {
	if(a > b) return a;
	else return b;

}
int getHeight(Node* root){
	if(!root) return 0;
	return root->height;
}

int getBalanceFactor(Node* root){
	return getHeight(root->left) - getHeight(root->right);
}

void updateHeight(Node* root){
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
}

Node* rotateRight(Node * root){
	Node* child = root->left;
	Node* gchild = child->right;
	
	child->right = root;
	root->left = gchild;
	
	updateHeight(root);
	updateHeight(child);
	
	return child;
}

Node* rotateLeft(Node * root){
	Node* child = root->right;
	Node* gchild = child->left;
	
	child->left = root;
	root->right = gchild;
	
	updateHeight(root);
	updateHeight(child);
	
	return child;
}

Node* rebalance(Node* root){
	int bf = getBalanceFactor(root);
	
	if(bf < -1){
		if(getBalanceFactor(root->right) > 0){
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}else if(bf > 1){
		
		if(getBalanceFactor(root->left) < 0){
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	return root;
}

Node* push(Node* root,char id[],char productName[],char productType[],char productStatus[],
				char description[],int productPrice){
	
	if(strcmp(productName, root->productName) < 0) {
	// kiri
		root->left = push(root->left,id ,productName, productType, productStatus,description, productPrice);
		
	}else if (strcmp(productName, root->productName) > 0){
	// kanan
		root->right = push(root->right, id ,productName, productType, productStatus,description, productPrice);
	}
	updateHeight(root);

	return rebalance(root);
}

Node* searchProduct(Node* root, char name[50]){
	if(!root) return NULL;
	if(strcmp(name, root->productName) < 0)
		return searchProduct(root->left, name);
	else if(strcmp(name, root->productName) > 0)
		return searchProduct(root->right, name);
	else return root;
}

int idIsValid(char* id){
	char random[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
				   	 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
				   	 'U', 'V', 'W', 'X', 'Y', 'Z'};
	id[0] = 'P', id[1] = 'R';
	for(int i = 2; i <= 4; i++){
		id[i] = random[rand()%sizeof(random)-1];
}
}
int words(char* check){
    int cnt = 1;
	for(int i = 0; i < strlen(check); i++){
		if(i != strlen(check)-1 && check[i] == ' ' && check[i+1] != '\0') cnt++;
	}
	if(cnt >= 2) return 1;
    return 0;
}

int endsWith(char* check, char* str){
    int len1 = strlen(check), len2 = strlen(str);
    if (len1 > len2) return 0;
    for (int i = 0; i < len1; ++i){
        if (check[len1 - 1 - i] != str[len2 - 1 - i]) return 0;
    }
    return 1;
}

Node* insertProduct(Node* root){
	char id[50];
	char productName[50];
	char productType[50];
	char productStatus[50];
	char description[100];
	int productPrice;
	do{
		printf("input product ID: ");
		scanf("%[^\n]", id);
		getchar();
//		len = strlen(id);
	}while(!idIsValid);
	
	do{
		printf("input product Name: ");
		scanf("%[^\n]", productName);
		getchar();
	} while(!words(productName));
	
	do{
		printf("input product Type: ");
		scanf("%[^\n]", &productType);
		getchar();
	}while(strcmp(productType, "Toys") && strcmp(productType, "Clothings") && strcmp(productType, "Electronic"));
	
	do{
		printf("input product Price: ");
		scanf("%d", &productPrice);
		getchar();
	}while(productPrice % 2 == 0);
	
		do{
		printf("input Description: ");
		scanf("%[^\n]", &description);
		getchar();
	}while(strlen(description) <= 30 || !endsWith("!!", description));
	
	do{
		printf("input product Type: ");
		scanf("%[^\n]", &productStatus);
		getchar();
	}while(strcmp(productStatus, "New") && strcmp(productType, "Second"));
	
	root = push(root, id ,productName, productType, productStatus, description,productPrice);
	
	return root;
};

void inOrder(Node* root){
	if(!root) return;
	inOrder(root->left);
	printf("%s | %s | %s | Rp. %d | %s | %s \n",root->id ,root->productName ,root->productType ,root->productPrice ,root->description,
												root->productStatus);
	inOrder(root->right);	
}

void preOrder(Node* root){
	if(!root) return;
	preOrder(root->left);
	printf("%s | %s | %s | Rp. %d | %s | %s \n",root->id ,root->productName ,root->productType ,root->productPrice ,root->description,
												root->productStatus);
	preOrder(root->left);	
	preOrder(root->right);	
}

void postOrder(Node* root){
	if(!root) return;
	postOrder(root->left);
	postOrder(root->left);	
	postOrder(root->right);
	printf("%s | %s | %s | Rp. %d | %s | %s \n",root->id ,root->productName ,root->productType ,root->productPrice ,root->description,
												root->productStatus);
}

void printData(Node* root){
	if(!root){
		printf("You don't have any product\n");
		return;
	}
		int satu = 0;
	
	scanf("%d", &satu);
	
	satu += satu;
	if(satu == 1){
		preOrder(root);
	}
	if(satu == 2){
		inOrder(root);
	}
	if(satu == 3){
		postOrder(root);
	}
	if(satu > 3){
		satu -= 3;
	}
	
};

Node* findPredecessor(Node* root){
	while(root->right){
		root = root->right;
	}
	return root;
}

Node* pop(Node* root, char productName[50]){
	if(!root) return NULL;
	
	if(strcmp(productName, root->productName) < 0) root->left = pop(root->left, productName);
	else if(strcmp(productName, root->productName) > 0)  root->right = pop(root->right, productName);
	else{
		if(!root->left && !root->right){
			root = NULL;
			free(root);
			return NULL;
		}else if(!root->left){
			Node* child = root->right;
			root = NULL;
			free(root);
			return child;
		}else if(!root->right){
			Node* child = root->left;
			root = NULL;
			free(root);
			return child;
		}else {
			Node* pre = findPredecessor(root);
			strcpy(root->id, pre->id);
			strcpy(root->productName, pre->productName);
			strcpy(root->productType, pre->productType);
			strcpy(root->productStatus, pre->productStatus);
			strcpy(root->description, pre->description);
			root->productPrice = pre->productPrice;
			
			root->left = pop (root->left, pre->id);
		}
	}
}

Node* deleteProduct(Node* root){
	if(!root){
		printf("You don't have any product\n");
		return NULL;
	}
	char id[50];
	char yn;
	Node* found = NULL;
	
	printData(root);
	
	do{
		printf("Enter ID to be removed:");
		scanf("%[^\n]", id);
		getchar();
		found = searchProduct(root, id);
	}while(!found);
		do{
			printf("Are you sure to delete this student? [Y / N] : ");
			scanf("%c", &yn); getchar();
		}while(yn != 'Y' && yn != 'N');
		if(yn == 'Y'){
			root = pop(root, id);
			puts("\nSuccess Deleted Student!");
		}
	getchar();
	return pop(root, id);
}

Node* clearAllData(Node* root){
	if(!root){
		puts("You dont have any production");
		return NULL;
	}
	char confirmation;
	do{
		printf("Are you sure you want to remove all product?");
		scanf("%c", &confirmation);
	}while(confirmation != 'Y' && confirmation != 'N');
	
	if(confirmation == 'Y'){
		while(root){
			root = pop(root, root->productName);
		}
	}
	return root;
}

int main(){
	int choose;
	do{
		puts("Welcome to toKApedia");
		puts("====================");
		puts("1. Change View Order");
		puts("2. Inser Product");
		puts("3. Delete Product");
		puts("4. Clear all product");
		puts("5. exit");
		printf(">> ");
		scanf("%d", &choose);
		getchar();
	
		switch(choose){
			case 1:
				printData(root);
				break;
			case 2:
				root = insertProduct(root);
				break;
			case 3:
				deleteProduct(root);
				break;
			case 4:
				clearAllData(root);
				break;
		}
	}while(choose != 5);
	
	return 0;
}
