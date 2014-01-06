#pragma once
#include "User.h"
#include "Graph.h"

class GraphFactory
{
public:
	static Graph * buildRandomGraph(int graphDepth, std::string email);
	static Graph * convertGraph(ns5__Graph * graph, string email);
};

