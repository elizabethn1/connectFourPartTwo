/**************************************************************************
 * This program replicates Connect 4 and builds off of Project 5.
 * (I modified some of my code from Program 5 to create Program 6.)
 * Two players take turns placing their piece into the board until
 * one of them is able to get their pieces to be four in a row
 * (horizontally, vertically, or diagonally), a player quits the game,
 * or the board is full and no one wins. This updated version of Program 5
 * also allows players to undo a move and print the past moves.
 * Class: CS 141, Fall 2023
 * System: CLion
 * @author Elizabeth Ng
 * @version December 1, 2023
 **************************************************************************/
#include <iostream>

using namespace std;

// This is the class for the board itself
class Connect4 {
private:
    char board[6][7]; // Private data member

public:
    // Constructor
    Connect4();

    // Functions of the Connect4 class
    void displayBoard();
    void makeMove(int columnChoice, char currentPlayer);
    bool columnFull(int columnChoice);
    bool diagonalDownCheck(char currentPlayer);
    bool diagonalUpCheck(char currentPlayer);
    bool horizontalCheck(char currentPlayer);
    bool verticalCheck(char currentPlayer);
    bool boardFull();
    bool boardEmpty();

};

// Connect4 constructor
Connect4::Connect4() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j] = '-';
        }
    }
}

/*
 * Description: Displays the Connect 4 board.
 * Input: N/A
 * Output: This function is of type void, so it doesn't return anything. However, it prints the 2D array, which is the board.
 */
void Connect4::displayBoard() {
    cout << "    0 1 2 3 4 5 6" << endl;

    for (int m = 0; m < 6; ++m) {
        cout << "    ";
        for (int n = 0; n < 7; ++n) {
            cout << board[m][n] << " ";
        }
        cout << endl;
    }
}

/*
 * Description: Updates the board to reflect a player's move.
 * Input: columnChoice (the column that a player chose for their move), currentPlayer (the player that is making a move)
 * Output: This function is of type void, so it doesn't return anything. However, this function updates the board to reflect a particular move that a player makes.
 */
void Connect4::makeMove(int columnChoice, char currentPlayer) {
    for (int row = 5; row >= 0; --row) { // Starts checking from the bottom of the column
        if (board[row][columnChoice] == '-') {
            board[row][columnChoice] = currentPlayer;
            break; // Exit out of the loop once the player's move has been made
        }
    }
}

/*
 * Description: Checks if the board's column is full.
 * Input: columnChoice (the column to check)
 * Output: isFull (If the column is full, return true. If not, return false)
 */
bool Connect4::columnFull(int columnChoice) {
    bool isFull = false;
    int counter = 0;

    for (int row = 5; row >= 0; --row) {
        if (board[row][columnChoice] != '-') {
            counter += 1; // Increments the counter by 1 because myBoard[row][columnChoice] contains an 'X' or 'O'
        }
    }

    if (counter == 6) {
        isFull = true; // Change the value of isFull from false to true because the column is full
    }

    return isFull;
}

/*
 * Description: Checks for a win that is diagonal and pointing downwards
 * Inputs: currentPlayer (the player that just made a move)
 * Output: foundWin (If the current player achieves a diagonal four in a row, return true. If not, return false)
 */
bool Connect4::diagonalDownCheck (char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (currentPlayer == board[row][col]) {
                if (board[row][col] == board[row + 1][col + 1]) {
                    if (board[row + 1][col + 1] == board[row + 2][col + 2]) {
                        if (board[row + 2][col + 2] == board[row + 3][col + 3]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks for a win that is diagonal and pointing upwards
 * Inputs: currentPlayer (the player that just made a move)
 * Output: foundWin (If the player achieves a diagonal four in a row, return true. If not, return false)
 */
bool Connect4::diagonalUpCheck (char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 3; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (currentPlayer == board[row][col]) {
                if (board[row][col] == board[row - 1][col + 1]) {
                    if (board[row - 1][col + 1] == board[row - 2][col + 2]) {
                        if (board[row - 2][col + 2] == board[row - 3][col + 3]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks for a win that's in a horizontal row
 * Inputs: currentPlayer (the player that just made a move)
 * Output: foundWin (If the player achieves a horizontal four in a row, return true. If not, return false)
 */
bool Connect4::horizontalCheck (char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (currentPlayer == board[row][col]) {
                if (board[row][col] == board[row][col + 1]) {
                    if (board[row][col + 1] == board[row][col + 2]) {
                        if (board[row][col + 2] == board[row][col + 3]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks for a win that's in a vertical row
 * Inputs: currentPlayer (the player that just made a move)
 * Output: foundWin (If the player achieves a vertical four in a row, return true. If not, return false)
 */
bool Connect4::verticalCheck(char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (currentPlayer == board[row][col]) {
                if (board[row][col] == board[row + 1][col]) {
                    if (board[row + 1][col] == board[row + 2][col]) {
                        if (board[row + 2][col] == board[row + 3][col]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks if the board is full
 * Inputs: N/A
 * Output: fullBoard (Returns true if the board is full. Returns false if the board isn't full.)
 */
bool Connect4::boardFull() {
    bool fullBoard = false;
    int counter = 0;

    // Only checks row 0 because if row 0 is full, the entire board must be full
    for (int a = 0; a < 7; ++a) {
        if (board[0][a] != '-') {
            counter += 1;
        }
    }

    if (counter == 7) {
        fullBoard = true;
    }

    return fullBoard;
}

/*
 * Description: Checks if the board is empty
 * Input: N/A
 * Output: emptyBoard (Returns true if the board is empty. Returns false if the board isn't empty.)
 */
bool Connect4::boardEmpty() {
    bool emptyBoard = false;
    int counter = 0;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (board[i][j] == '-') {
                counter += 1;
            }
        }
    }

    if (counter == 42) {
        emptyBoard = true;
    }

    return emptyBoard;
}

// This is the class for nodes
class BoardNode {
private:
    // Private data members
    Connect4 gameBoard;
    BoardNode* link;

public:
    // Constructor
    BoardNode(Connect4 gameBoard);

    // Functions of the BoardNode class (also includes accessors and a mutator)
    Connect4 getData();
    BoardNode* getLink();
    void setLink(BoardNode *link);
};

// BoardNode constructor
BoardNode::BoardNode(Connect4 gameBoard) {
    this->gameBoard = gameBoard;
    this->link = nullptr;
}

/*
 * Description: BoardNode accessor for a Connect4 object, which is the node's data
 * Input: N/A
 * Output: this->gameBoard() (Returns a private data member of the BoardNode class, which is a Connect4 object.)
 */
Connect4 BoardNode::getData() {
    return this->gameBoard;
}

/*
 * Description: BoardNode accessor for link, which is the node's link
 * Input: N/A
 * Output: link (Returns a private data member of the BoardNode class, which is a pointer.)
 */
BoardNode* BoardNode::getLink() {
    return link;
}

/*
 * Description: BoardNode mutator for link, which is the node's link
 * Input: link (A BoardNode pointer)
 * Output: This function is of type void, so it doesn't return anything. However, it sets this BoardNode object's link to another node's link
 */
void BoardNode::setLink(BoardNode* link) {
    this->link = link;
}

// This is a class for the linked list that contains nodes
class BoardLinkedList {
private:
    // Private data members
    BoardNode* head;

    void printBackwards(BoardNode* node); // A recursive function that's a private data member. It's used to print the linked list backwards.

public:
    // Constructor
    BoardLinkedList();

    // Functions of the BoardLinkedList class (also includes an accessor)
    Connect4 getFirstNode();

    void addToBeginning(Connect4 b);
    void removeFromBeginning();
    void printBackwards();
    bool headNull();
};

// BoardLinkedList constructor
BoardLinkedList::BoardLinkedList() {
    head = nullptr;
}

/*
 * Description: An accessor that returns the data (a Connect4 object) of the linked list's beginning node.
 * Input: N/A
 * Output: head->getData() (Returns a Connect4 object)
 */
Connect4 BoardLinkedList::getFirstNode() {
    return head->getData();
}

/*
 * Description: Creates a node with the Connect4 object and that node gets added to the beginning of the linked list
 * Input: board (a Connect4 object that will be used to create a new node)
 * Output: This function is of type void, so it doesn't return anything.
 */
void BoardLinkedList::addToBeginning(Connect4 board) {
    BoardNode* newNode = new BoardNode(board);
    newNode->setLink(this->head);
    head = newNode;
}

/*
 * Description: Removes the node that's at the beginning of the linked list
 * Input: N/A
 * Output: This function is of type void, so it doesn't return anything.
 */
void BoardLinkedList::removeFromBeginning() {
    BoardNode* temp = head;
    head = head->getLink();
    delete temp;
}

/*
 * Description: A recursive function that helps with printing the linked list backwards, which will print the past moves in order. The actual printing doesn't happen here.
 * Input: N/A
 * Output: This function is of type void, so it doesn't return anything. However, it calls the printBackwards() function that takes a paramater of head.
 */
void BoardLinkedList::printBackwards() {
    if (head != nullptr) {
        printBackwards(head);
    }
}

/*
 * Description: A recurive function that is used to print the linked list backwards, which will print the past moves in order.
 * Input: node (a BoardNode pointer)
 * Output: This function is of type void, so it doesn't return anything. However, each node's board will be printed using the displayBoard() function.
 */
void BoardLinkedList::printBackwards(BoardNode* node) {
    if (node->getLink() != nullptr) {
        printBackwards(node->getLink());
    }

    cout << endl;
    cout << endl;
    node->getData().displayBoard(); // Print the current node
}

/*
 * Description: Checks if the head of the linked list is pointing to nullptr or not.
 * Input: N/A
 * Output: isNull (Returns true if the head is pointing to nullptr. Returns false if the head is not pointing to nullptr)
 */
bool BoardLinkedList::headNull() {
    bool isNull;

    if (head == nullptr) {
        isNull = true;
    }
    else {
        isNull = false;
    }

    return isNull;
}

int main()
{
    // Directions for the game
    cout << "This is the Game Connect 4." << endl;
    cout << "Each player should place an X or an O in the space" << endl;
    cout << "by entering the column you want to place the piece." << endl;
    cout << "The piece will fall until it reaches the bottom or" << endl;
    cout << "the current pieces in the board. When X or O gets 4 in" << endl;
    cout << "a row (either horizontally, vertically, or diagonally," << endl;
    cout << "then that person wins. The user can enter Q (or q) to" << endl;
    cout << "end the game early." << endl;
    cout << "Let's get started!!!" << endl;

    Connect4 myBoard; // Connect4 object

    BoardLinkedList pastMovesList; // BoardLinkedList object

    myBoard.displayBoard(); // Display the board, which is currently empty

    int playerCounter = 0; // Initialized to 0 so that player X will make the first move
    char playerInput;
    char player;

    do {
        // Allows the players to take turns while they play the game. If playerCounter is an even integer, X plays. If playerCounter is an odd integer, O plays.
        if ((playerCounter % 2) == 0) {
            player = 'X';
            cout << "It is X's turn." << endl;
        } else if ((playerCounter % 2) == 1) {
            player = 'O';
            cout << "It is O's turn." << endl;
        }

        cout << "Enter a column to place your piece.";
        cin >> playerInput;

        if ((playerInput == 'Q') || (playerInput == 'q')) { // A player wants to quit the game
            cout << "Ending Game" << endl;
            break;
        }
        else if ((playerInput == 'P') || (playerInput == 'p')) { // A player wants to print the past moves
            pastMovesList.printBackwards(); // Print the past moves recursively backwards
            pastMovesList.getFirstNode().displayBoard(); // Display the most recent move
        }
        else if ((playerInput == 'U') || (playerInput == 'u')) { // A player wants to undo a move
            if (myBoard.boardEmpty() == false) { // Board is not empty
                pastMovesList.removeFromBeginning(); // Removes the first node of the linked list

                if (pastMovesList.headNull() == false) {
                    pastMovesList.getFirstNode().displayBoard(); // Display the most recent move
                    myBoard = pastMovesList.getFirstNode(); // Update myBoard to reflect the head of the linked list
                    playerCounter += 1; // Increment playerCounter by 1 at the end of the turn so that it can be the next player's turn
                }
                else {
                    Connect4 temp;
                    myBoard = temp; // Updates myBoard to an empty board
                    myBoard.displayBoard(); // Display the board
                    playerCounter += 1; // Increment playerCounter by 1 at the end of the turn so that it can be the next player's turn
                }
            }
            else {
                myBoard.displayBoard(); // Board is empty. Display the board.
            }
        }
        else if ((int(playerInput) >= 48) && (int(playerInput) <= 54)) { // If this is true, this means that the user's input is a valid column.
            int columnSelection = int(playerInput - '0'); // Stores the column as an int

            if (myBoard.columnFull(columnSelection) == false) { // If the column is not full, the player can make their move. If it's full, they have to enter another input.
                myBoard.makeMove(columnSelection, player); // Player makes a move

                pastMovesList.addToBeginning(myBoard); // This will create a node that contains myBoard, which will be added to the beginning of the linked list

                myBoard.displayBoard(); // Display the board

                // Checks for a win. Four different checks are made on the board.
                if (player == 'X') {
                    if (myBoard.diagonalDownCheck('X') || myBoard.diagonalUpCheck('X') || myBoard.horizontalCheck('X') || myBoard.verticalCheck('X')) {
                        cout << "Game is Over, Player X got 4 in a row!!!!" << endl;
                        break;
                    }
                }
                else if (player == 'O') {
                    if (myBoard.diagonalDownCheck('O') || myBoard.diagonalUpCheck('O') || myBoard.horizontalCheck('O') || myBoard.verticalCheck('O')) {
                        cout << "Game is Over, Player O got 4 in a row!!!!" << endl;
                        break;
                    }
                }

                playerCounter += 1; // Increment playerCounter by 1 at the end of the turn so that it can be the next player's turn
            }
            else {
                cout << "column chosen is already full" << endl;
            }
        }
        else {
            cout << "Please enter a valid column" << endl;
        }
    } while (myBoard.boardFull() != true); // The players will be prompted to play the game as long as the board isn't full and no one has won

    if (myBoard.boardFull()) { // Checks if the board is full
        cout << "Board is Full, It's a Draw!!!" << endl;
    }

    return 0;
}

