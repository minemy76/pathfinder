#include <fstream>
#include "maze.h"

void graph::drawGraph(){
	std::ofstream graph("graphDrawer.gv");
    if (graph.is_open()) {
        graph << "digraph path{\n"
            << "rankdir = LR;\n"
            << "OPEN[shape=\"rectangle\",style=\"filled\",fillcolor=\"lightgrey\", label=\"START\"];\n"
            << "CLOSED[shape = \"rectangle\", label = \"END\"];\n"

            << "OPEN->CLOSED\n;"

            << "}";
        graph.close();
    }
}