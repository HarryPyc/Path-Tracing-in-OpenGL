#include "KdTree.h"


void KdTree::ConstructKdTree()
{
	CalculateCenter();
	TreeNode root(glm::vec3(0), glm::vec3(300, 300, 1200));
	helper(root, triangleList.begin(), triangleList.end());
	nodeList.push_back(root);
	vector<glm::uvec4> temp;
	for (int i = 0; i < triangleList.size(); i++) {
		temp.push_back(Triangles[triangleList[i].index]);
	}
	Triangles = temp;
}

bool compX(const Triangle& t0, const Triangle& t1), compY(const Triangle& t0, const Triangle& t1), compZ(const Triangle& t0, const Triangle& t1);
void KdTree::helper(TreeNode &root, iter begin, iter end)
{
	//sort triangles in split axis
	glm::vec3 diag = root.maxBb - root.minBb;
	root.axis = diag.x > diag.y && diag.x > diag.z ? 0 : (diag.y > diag.z ? 1 : 2);
	glm::vec3 split = root.maxBb;
	root.firstTriangle = begin - triangleList.begin();
	root.triangleCount = end - begin;
	if (root.triangleCount <= MAX_TRIANGLE_IN_LEAF) {
		root.isLeaf = true;
		return;
	}
	iter midIt = begin + (end-begin) / 2;
	switch (root.axis)
	{
	case 0: sort(begin, end, compX); split.x = midIt->center.x+1.f; break;
	case 1: sort(begin, end, compY); split.y = midIt->center.y+1.f; break;
	case 2: sort(begin, end, compZ); split.z = midIt->center.z+1.f; break;
	}


	//for (iter it = begin; it < end; it++) {
	//	if (glm::all(glm::lessThanEqual(it->center, split)))
	//		midIt++;
	//}

	if (midIt != begin) {
		TreeNode left(root.minBb, split);
		helper(left, begin, midIt);
		nodeList.push_back(left); root.left = nodeList.size() - 1;
	}
	if (midIt != end) {
		TreeNode right(split, root.maxBb);
		helper(right, midIt, end);
		nodeList.push_back(right); root.right = nodeList.size() - 1;
	}
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