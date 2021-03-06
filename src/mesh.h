/*
 * Copyright (c) 2015, DriveAI
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of whiskey-foxtrot nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
* Mesh.h
* @author: Travis Vanderstad, Parth Mehrotra
*
* Mesh represents a triangular mesh. Stores a list of triangles (see Triangle.h) and vertices (see MeshTriple.h)
* triangles store references to their verts and verts to their triangels
*/

#pragma once
#ifndef SRC_MESH_H_
#define SRC_MESH_H_

#include <vector>

#include "triple.h"
#include "triangle.h"
#include "mesh_triple.h"
#include "nd_array.h"

#define start_size 5;

class Mesh {
 public:
	/**
	* makes the triangulation. boom.
	* @param cList pointer to a CoordinateList
	*/
	explicit Mesh(CoordinateList* cList);

	/**
	* result of the triangulation: an image full of interpolation ranges
	*/
	NdArray<float>* result;

 private:
	/**
	* hull for sweeping (the sweep-hull. s-hull. more on this at www.s-hull.org/)
	*/
	std::vector<MeshTriple*> hull;

	/**
	* all the verts in the triangulation
	*/
	std::vector<MeshTriple*> verts;

	/**
	* all the triangles in the triangulation
	*/
	std::vector<Triangle*> tris;

	/**
	* all coordinates that are
	*/
	CoordinateList* list;

	/**
	* pick a seed point for the triangulation
	*
	* @return A pointer to a MeshTriple to begin triangulation
	*/
	MeshTriple* chooseSeed();

	/**
	* generate the initial hull
	*
	* @param index0 index of the first Triple
	* @param index1 index of the second Triple
	* @param index2 index of the third Triple
	*/
	void initHull(size_t index0, size_t index1, size_t index2);

	/**
	* add a vertex to the triangulation. this is called for each entry in list
	*
	* @param v pointer to the vertex being inserted
	*/
	void insertVert(Triple* v);

	/**
	* do what needs to be done to remove a triangle
	*
	* @param t pointer to triangle being removed
	*/
	void removeTri(Triangle* t);

	/**
	* get a list of a vertex's neighboring vertices
	*
	* @param t point to find neighbors from
	* @return vector of neighboring points
	*/
	static std::vector<MeshTriple*> getNeighbors(MeshTriple* t);

	/**
	* get a list of a triangle's neighboring triangles
	*
	* @param t triangle to find neighbors from
	* @return vector of neighboring Triangles
	*/
	static std::vector<Triangle*> getNeighbors(Triangle* t);

	/**
	* determines if one triple is "visible" to another through the hull (does a line between them intersect the hull lines)
	*
	* @param a first Triple
	* @param d second Triple
	*/
	bool isVisible(Triple& a, Triple& d);

	/**
	* tests if the lines formed by two pairs of Triples intersects
	*
	* @param p1 first point on line 1
	* @param q1 first point on line 2
	* @param p2 second point on line 1
	* @param q2 second point on line 2
	*/
	static bool testIntersect(Triple p1, Triple q1, Triple p2, Triple q2);

	/**
	* TODO better description
	*/
	static bool onSegment(Triple p, Triple q, Triple r);

	/**
	* TODO better description
	*/
	static int orientation(Triple p, Triple q, Triple r);

	static bool inCircumCirc(Triple* t0, Triple* t1, Triple* t2, Triple* p);

	static float det(float** in_matrix, int n);

	int flip(Triangle* t);

	/**
	* populated with data from all neighbors of the triangulation's nearest vert
	*/
	NdArray<float>* data;

	MeshTriple* getNearest(Triple &t);

	static float dist2(const Triple &a, const Triple &b);

	static int toPixelX(float x);

	static int toPixelY(float y);

	static float toImageX(int x);

	static float toImageY(int y);
};

#endif  // SRC_MESH_H_

