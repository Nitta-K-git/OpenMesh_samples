#include <iostream>
#include <vector>
// -------------------- OpenMesh
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;
int main(int argc, char **argv) {
    MyMesh mesh;
    // check command line options
    if(argc != 2) {
        std::cerr << "Usage:  " << argv[0] << " infile\n";
        return 1;
    }
    // read mesh from stdin
    if(!OpenMesh::IO::read_mesh(mesh, argv[1])) {
        std::cerr << "Error: Cannot read mesh from " << argv[1] << std::endl;
        return 1;
    }
	
    MyMesh::VertexIter v_it, v_end(mesh.vertices_end());
    MyMesh::VertexVertexIter vv_it; // circulator:1ring vertex
    for(v_it = mesh.vertices_begin(); v_it != v_end; ++v_it) {
		std::cout << "vertex: " << v_it->idx() << ", manifold: " << mesh.is_manifold(v_it) << std::endl;
        for(vv_it = mesh.vv_iter(*v_it); vv_it.is_valid(); ++vv_it) {
			std::cout << vv_it->idx() << ", ";
        }
		std::cout << std::endl;
    }

	MyMesh::FaceIter f_it, f_end(mesh.faces_end());
	MyMesh::FaceFaceIter ff_it;
	for (f_it = mesh.faces_begin(); f_it != f_end; ++f_it) {
		std::cout << "face: " << f_it->idx() << std::endl;
		for (ff_it = mesh.ff_iter(*f_it); ff_it.is_valid(); ++ff_it) {
			std::cout << ff_it->idx() << ", ";
		}
		std::cout << std::endl;
	}
    return 0;
}