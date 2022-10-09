#pragma once
#include "Time.h"
#include "Box.h"
#include "MyLib.h"
#include "DataTypes.h"
#include <iomanip>
#include <string.h>
#include <conio.h>
#include "ReadAndWriteFiles.h"
#include <vector>
#include <ctime>
#include <sstream>

// PassengerList class definition
PassengerList::PassengerList() {
	root = nullptr;
	pCount = 0;
}

PassengerList::~PassengerList() {
	clear();
}

void PassengerList::clear() {
	postOrderDeleteTree(root);
	pCount = 0;
}

void PassengerList::postOrderDeleteTree(Passenger* subroot) {
	if (subroot != nullptr) {
		postOrderDeleteTree(subroot->left);
		postOrderDeleteTree(subroot->right);
		delete subroot;
		subroot = nullptr;
	}
}

bool PassengerList::insertPassenger(const string& ssid, const string& lastname,
	const string& firstname, const SEX& sex) {
	Passenger* newpassenger = new Passenger(ssid, lastname, firstname, sex);
	bool check = true;
	root = recursiveInsert(root, newpassenger, check);
	if (check == true)
		pCount++;
	return check;
}

Passenger* PassengerList::recursiveInsert(Passenger* subroot, Passenger* newpassenger,
	bool& check) {
	if (subroot == nullptr) {
		subroot = newpassenger;
		return subroot;
	}
	if (newpassenger->sSID.compare(subroot->sSID) < 0)
		subroot->left = recursiveInsert(subroot->left, newpassenger, check);
	else if (newpassenger->sSID.compare(subroot->sSID) > 0)
		subroot->right = recursiveInsert(subroot->right, newpassenger, check);
	else {
		check = false;
		return subroot;
	}
	int bf = getBalanceFactor(subroot);
	if (bf > 1 && newpassenger->sSID.compare(subroot->left->sSID) < 0)
		return rotateRight(subroot);
	if (bf < -1 && newpassenger->sSID.compare(subroot->right->sSID) > 0)
		return rotateLeft(subroot);
	if (bf > 1 && newpassenger->sSID.compare(subroot->left->sSID) > 0) {
		rotateLeft(subroot->left);
		return rotateRight(subroot);
	}
	if (bf < -1 && newpassenger->sSID.compare(subroot->right->sSID) < 0) {
		rotateRight(subroot->right);
		return rotateLeft(subroot);
	}
	return subroot;
}

Passenger* PassengerList::rotateLeft(Passenger* subroot) {
	Passenger* righttree = subroot->right;
	subroot->right = righttree->left;
	righttree->left = subroot;
	return righttree;
}

Passenger* PassengerList::rotateRight(Passenger* subroot) {
	Passenger* lefttree = subroot->left;
	subroot->left = lefttree->right;
	lefttree->right = subroot;
	return lefttree;
}

void PassengerList::deletePassenger(const string& ssid) {
	root = recursiveDelete(root, ssid);
	pCount--;
}

Passenger* PassengerList::recursiveDelete(Passenger* subroot, const string& ssid) {
	if (subroot == nullptr)
		return subroot;
	if (ssid.compare(subroot->sSID) < 0)
		subroot->left = recursiveDelete(subroot->left, ssid);
	else if (ssid.compare(subroot->sSID) > 0)
		subroot->right = recursiveDelete(subroot->right, ssid);
	else {
		if (subroot->left == nullptr) {
			Passenger* temp = subroot->right;
			delete subroot;
			subroot = temp;
		}
		else if (subroot->right == nullptr) {
			Passenger* temp = subroot->left;
			delete subroot;
			subroot = temp;
		}
		else {
			Passenger* temp = minValuePassenger(subroot->right);
			copyPassengerData(subroot, temp);
			recursiveDelete(subroot->right, temp->sSID);
		}
	}
	int bf = getBalanceFactor(subroot);
	if (bf == 2 && getBalanceFactor(subroot->left) >= 0)
		return rotateRight(subroot);
	else if (bf == 2 && getBalanceFactor(subroot->left) == -1) {
		rotateLeft(subroot->left);
		return rotateRight(subroot);
	}
	else if (bf == 2 && getBalanceFactor(subroot->right) <= 0)
		return rotateLeft(subroot);
	else if (bf == 2 && getBalanceFactor(subroot->right) > 0) {
		rotateLeft(subroot->right);
		return rotateRight(subroot);
	}
	return subroot;
}

Passenger* PassengerList::minValuePassenger(Passenger* parent) {
	Passenger* p = parent;
	while (p->left != nullptr)
		p = p->left;
	return p;
}

int PassengerList::height(Passenger* subroot) {
	if (subroot == nullptr)
		return -1;
	int lHeight = height(subroot->left);
	int rHeight = height(subroot->right);
	return ((lHeight > rHeight) ? lHeight + 1 : rHeight + 1);
}

int PassengerList::getBalanceFactor(Passenger* subroot) {
	if (subroot == nullptr)
		return -1;
	return (height(subroot->left) - height(subroot->right));
}

void PassengerList::copyPassengerData(Passenger* lhs, Passenger* rhs) {
	lhs->sSID = rhs->sSID;
	lhs->firstName = rhs->firstName;
	lhs->lastName = rhs->lastName;
	lhs->sex = rhs->sex;
}

const Passenger* PassengerList::searchPassenger(const string& ssid) const {
	Passenger* pSearch = root;
	while (pSearch != nullptr &&
		pSearch->sSID.compare(ssid) != 0) {
		if (ssid.compare(pSearch->sSID) < 0)
			pSearch = pSearch->left;
		else
			pSearch = pSearch->right;
	}
	return pSearch;
}

void PassengerList::addPassengerToVector(vector<Passenger*>& v) const {
	inOrderDFT(root, v);
}

void PassengerList::inOrderDFT(Passenger* subroot, vector<Passenger*>& v) const {
	if (subroot != nullptr) {
		inOrderDFT(subroot->left, v);
		v.push_back(subroot);
		inOrderDFT(subroot->right, v);
	}
}

int PassengerList::getTotalPassenger() const {
	return pCount;
}

// Passengers class definition
Passenger::Passenger(string ssid, string ln, string fn, SEX sex)
	: sSID(sSID), lastName(ln), firstName(fn), sex(sex) {
	left = right = nullptr;
	BF = 0;
}