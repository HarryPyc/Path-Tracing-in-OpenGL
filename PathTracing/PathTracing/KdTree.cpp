#include "KdTree.h"


void KdTree::ConstructKdTree()
{
	CalculateCenter();
	TreeNode root;
	helper(root, triangleList.begin(), triangleList.end(), glm::vec3(0), glm::vec3(300), 0);
	nodeList.insert(nodeList.begin(), root);
	vector<glm::uvec4> temp;
	for (int i = 0; i < triangleList.size(); i++) {
		temp.push_back(Triangles[triangleList[i].index]);
	}
	Triangles = temp;
}

bool compX(const Triangle& t0, const Triangle& t1), compY(const Triangle& t0, const Triangle& t1), compZ(const Triangle& t0, const Triangle& t1);
void KdTree::helper(TreeNode &root, iter begin, iter end, glm::vec3 minBb, glm::vec3 maxBb, int depth)
{
	root.firstTriangle = begin - triangleList.begin();
	root.triangleCount = end - begin;
	if (root.triangleCount <= MAX_TRIANGLE_IN_LEAF || ++depth > MAX_DEPTH) {
		root.isLeaf = true;
		return;
	}

	glm::vec3 diag = maxBb - minBb;
	root.axis = diag.x > diag.y && diag.x > diag.z ? 0 : (diag.y > diag.z ? 1 : 2);
	//sort triangles in split axis
	switch (root.axis)
	{
	case 0: sort(begin, end, compX);  break;
	case 1: sort(begin, end, compY);  break;
	case 2: sort(begin, end, compZ);  break;
	}
	diag[root.axis] /= 2.f;
	glm::vec3 split = minBb + diag;
	root.val = split[root.axis];

	iter midIt = begin;
	for (iter it = begin; it < end; it++) {
		if (it->center[root.axis] < root.val)
			midIt++;
		else
			break;
	}

	
	TreeNode left;
	helper(left, begin, midIt, minBb, split, depth);
	nodeList.push_back(left); root.left = nodeList.size() ;
	

	TreeNode right;
	helper(right, midIt, end, split, maxBb, depth);
	nodeList.push_back(right); root.right = nodeList.size() ;
	
}

void KdTree::CalculateCenter()
{
	for (int i = 0; i < Triangles.size(); i++) {
		const glm::vec4 v0 = Vertices[Triangles[i].x], v1 = Vertices[Triangles[i].y], v2 = Vertices[Triangles[i].z];
		glm::vec3 center = glm::vec3(v0 + v1 + v2) / 3.f;
		triangleList.push_back(Triangle(i, center));
	}
}

bool compX(const Triangle& t0, const Triangle& t1) {
	return t0.center.x < t1.center.x;
}
bool compY(const Triangle& t0, const Triangle& t1) {
	return t0.center.y < t1.center.y;
}
bool compZ(const Triangle& t0, const Triangle& t1) {
	return t0.center.z < t1.center.z;
}