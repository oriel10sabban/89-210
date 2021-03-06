/*
 * StandartRules_test.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: guyzach
 */
#include "../gtest_src/gtest/gtest.h"
#include "../src/ComputerPlayer.h"
#include "../src/StandartRules.h"
#include "../src/Board.h"
#include "../src/Point.h"
#include <list>
#define R1 8
#define C1 8
using namespace std;

bool checkIfPointInList2(Point p, list<Point> listOfPoints) {
  for (list<Point>::iterator it = listOfPoints.begin();
      it != listOfPoints.end(); ++it) {
    if ((p.getX() == it->getX()) && (p.getY() == it->getY())) {
      return true;
    }
  }
  return false;
}
//Check the method bool checkIfIsALegalMove(bool isWhite, Point point, Board* board) const
//Check move on legal  cells
TEST(StandartRulesTest, checkIfIsALegalMove1) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();

    EXPECT_TRUE(sRules.checkIfIsALegalMove(isWhite,Point(2,4),&b3));
    EXPECT_TRUE(sRules.checkIfIsALegalMove(isWhite,Point(3,5),&b3));
    EXPECT_TRUE(sRules.checkIfIsALegalMove(isWhite,Point(4,2),&b3));
    EXPECT_TRUE(sRules.checkIfIsALegalMove(isWhite,Point(5,3),&b3));

    EXPECT_TRUE(sRules.checkIfIsALegalMove(!isWhite,Point(3,2),&b3));
    EXPECT_TRUE(sRules.checkIfIsALegalMove(!isWhite,Point(2,3),&b3));
    EXPECT_TRUE(sRules.checkIfIsALegalMove(!isWhite,Point(4,5),&b3));
    EXPECT_TRUE(sRules.checkIfIsALegalMove(!isWhite,Point(5,4),&b3));
}
//Check move on taken cells
TEST(StandartRulesTest, checkIfIsALegalMove2) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();

    EXPECT_FALSE(sRules.checkIfIsALegalMove(isWhite,Point(3,3),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(isWhite,Point(4,4),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(isWhite,Point(4,3),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(isWhite,Point(3,4),&b3));
}
TEST(StandartRulesTest, checkIfIsALegalMove3) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();

    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(1,1),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(6,6),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(1,6),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(6,1),&b3));
}
TEST(StandartRulesTest, checkIfIsALegalMove4) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();

    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(-1,-1),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(-1,1),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(-1,1),&b3));
    EXPECT_FALSE(sRules.checkIfIsALegalMove(!isWhite,Point(R1,C1),&b3));
}

//Check the method bool areThePlayerHasALegalMove(bool isWhite, Board* board) const
TEST(StandartRulesTest, areThePlayerHasALegalMove1) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();
    EXPECT_TRUE(sRules.areThePlayerHasALegalMove(isWhite,&b3))
    << "there is no recognition of legal moves for 'white'";
    EXPECT_TRUE(sRules.areThePlayerHasALegalMove(!isWhite,&b3))
    << "there is no recognition of legal moves for 'black";
}
//Check full board
TEST(StandartRulesTest, areThePlayerHasALegalMove2) {
	bool isWhite=true;
    Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();
    for(int i=0;i<C1;i++){
    	for(int j=0;j<R1;j++){
    		b3.setValueAt(i,j,W);
    	}
    }
    EXPECT_FALSE(sRules.areThePlayerHasALegalMove(isWhite,&b3))
    << "there is incorrect recognition of legal moves for 'white";
    EXPECT_FALSE(sRules.areThePlayerHasALegalMove(!isWhite,&b3))
    << "there is incorrect recognition of legal moves for 'black";
}
TEST(StandartRulesTest, areThePlayerHasALegalMove3) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();
    //putting 'white' all over the board except last row and last column
    for(int i=1;i<C1-1;i++){
    	for(int j=1;j<R1-1;j++){
    		b3.setValueAt(i,j,W);
    	}
    }
    for(int i=0;i<C1-1;i++){
    	b3.setValueAt(0,i,B);
    	b3.setValueAt(i,0,B);
    }
    EXPECT_TRUE(sRules.areThePlayerHasALegalMove(!isWhite,&b3))
    << "there is no recognition of legal moves for 'black";
    EXPECT_FALSE(sRules.areThePlayerHasALegalMove(isWhite,&b3))
    << "there is incorrect recognition of legal moves for 'white";
}
//Check the method list<Point> theLegalMovesOfPlayer(bool isWhite, Board* board) const
//Check starting board
TEST(StandartRulesTest, theLegalMovesOfPlayer1) {
	bool isWhite=true;
    Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();

    listOfCorrectPoints.push_back(Point(2, 4));
    listOfCorrectPoints.push_back(Point(4, 2));
    listOfCorrectPoints.push_back(Point(3, 5));
    listOfCorrectPoints.push_back(Point(5, 3));

    listOfPointsFromFunction = sRules.theLegalMovesOfPlayer(isWhite,&b3);

    for (list<Point>::iterator it = listOfCorrectPoints.begin();it != listOfCorrectPoints.end(); ++it) {
    	EXPECT_TRUE(checkIfPointInList2(*it, listOfPointsFromFunction)) << "the Point ("
    	<< it->getX() << "," << it->getY() << ") is an option, but not recognized as one";
    }
}


//Check if margins are founded as an option
TEST(StandartRulesTest, theLegalMovesOfPlayer2) {
	bool isWhite=true;
	Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();
    //putting 'white' all over the board except last row and last column
    for(int i=1;i<C1-1;i++){
        for(int j=1;j<R1-1;j++){
       		b3.setValueAt(i,j,W);
       	}
    }
    for(int i=0;i<C1-1;i++){
       	b3.setValueAt(0,i,B);
       	b3.setValueAt(i,0,B);
    }
    //insert the expected options for 'black
    for(int i=1;i<C1-1;i++){
        listOfCorrectPoints.push_back(Point(i, 7));
        listOfCorrectPoints.push_back(Point(7, i));
    }
    listOfCorrectPoints.push_back(Point(7, 7));
    listOfPointsFromFunction = sRules.theLegalMovesOfPlayer(!isWhite,&b3);

    for (list<Point>::iterator it = listOfCorrectPoints.begin(); it != listOfCorrectPoints.end(); ++it) {
        EXPECT_TRUE(checkIfPointInList2(*it, listOfPointsFromFunction)) << "the Point ("
        << it->getX() << "," << it->getY() << ") is an option, but not recognized as one";
    }
}
//Check full board
TEST(StandartRulesTest, theLegalMovesOfPlayer3) {
	bool isWhite=true;
    Board b3 = Board(R1, C1);
    StandartRules sRules = StandartRules();
    list< Point> listOfPointsFromFunction;
    list< Point> listOfCorrectPoints;
    listOfPointsFromFunction.clear();
    listOfCorrectPoints.clear();
    for(int i=0;i<C1;i++){
    	for(int j=0;j<R1;j++){
    		b3.setValueAt(i,j,W);
    	}
    }
    listOfPointsFromFunction = sRules.theLegalMovesOfPlayer(isWhite,&b3);
    EXPECT_TRUE(listOfPointsFromFunction.size()==0) << "The board is full"
  	" but the function found options for the white player";
    listOfPointsFromFunction = sRules.theLegalMovesOfPlayer(!isWhite,&b3);
    EXPECT_TRUE(listOfPointsFromFunction.size()==0) << "The board is full"
    " but the function found options for the black player";
}
