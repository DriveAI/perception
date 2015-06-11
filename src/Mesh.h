// Mesh.h
// @author: Travis Vanderstad, Parth Mehrotra

// Mesh represents a triangular mesh. Stores a list of triangles (see Triangle.h) and vertices (see MeshTriple.h)
// triangles store references to their verts and verts to their triangels

#pragma once

#include <vector>

#include "Triple.h"
#include "Triangle.h"
#include "MeshTriple.h"

#define start_size 5;

class Mesh {
	public:
		// makes the triangulation. boom.
		Mesh(CoordinateList* cList);

	private:
		// hull for sweeping (the sweep-hull. s-hull. more on this at www.s-hull.org/)
		vector<MeshTriple*> hull;

		// all the verts in the triangulation
		vector<MeshTriple*> verts;

		// all the triangles in the triangulation
		vector<Triangle*> tris;

		// all coordinates that are
		CoordinateList* list;

		// pick a seed point for the triangulation
		MeshTriple* chooseSeed();

		// generate the initial hull
		void initHull(size_t index0, size_t index1, size_t index2);

		// add a vertex to the triangulation. this is called for each entry in list
		void insertVert(Triple t);

		// get a list of a vertex's neighboring vertices
		vector<MeshTriple*> getNeighbors(MeshTriple* t);

		// get a list of a triangle's neighboring triangles
		vector<Triangle*> getNeighbors(Triangle* t);

		// determines if one triple is "visible" to another through the hull (does a line between them intersect the hull lines)
		bool isVisible(Triple& a, Triple& d);

		// helper function for above function
		bool testIntersect(Triple p1, Triple q1, Triple p2, Triple q2);

		// helper-helper function for above function
		bool onSegment(Triple p, Triple q, Triple r);

		// helper-helper function for function above above function
		int orientation(Triple p, Triple q, Triple r);
};
