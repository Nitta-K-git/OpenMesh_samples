#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Utils/PropertyManager.hh>
#include <iostream>
#include <vector>
using MyMesh = OpenMesh::TriMesh_ArrayKernelT<>;
int main(int argc, char **argv) {
    // Read command line options
    MyMesh mesh;
    if(argc != 4) {
        std::cerr << "Usage: " << argv[0] << " #iterations infile outfile" << std::endl;
        return 1;
    }
    const int iterations = atoi(argv[1]);
    const std::string infile = argv[2];
    const std::string outfile = argv[3];

    // Read mesh file
    if(!OpenMesh::IO::read_mesh(mesh, infile)) {
        std::cerr << "Error: Cannot read mesh from " << infile << std::endl;
        return 1;
    }
    {
        // Add a vertex property storing the computed centers of gravity
        auto cog = OpenMesh::makeTemporaryProperty<OpenMesh::VertexHandle, MyMesh::Point>(mesh);
        // Smooth the mesh several times
        for(int i = 0; i < iterations; ++i) {
            // Iterate over all vertices to compute centers of gravity
            for(const auto &vh : mesh.vertices()) {
                cog[vh] = {0, 0, 0};
                int valence = 0;
                // Iterate over all 1-ring vertices around vh
                for(const auto &vvh : mesh.vv_range(vh)) {
                    cog[vh] += mesh.point(vvh);
                    ++valence;
                }
                cog[vh] /= valence;
            }
            // Move all vertices to the previously computed positions
            for(const auto &vh : mesh.vertices()) {
                mesh.point(vh) = cog[vh];
            }
        }
    } // The cog vertex property is removed from the mesh at the end of this scope

    // create permanent property
    auto face_area = OpenMesh::getOrMakeProperty<OpenMesh::FaceHandle, double>(mesh, "face_area");

    try {
        auto face_area2 = OpenMesh::getProperty<OpenMesh::FaceHandle, double>(mesh, "face_area");
        // Use the face_area property.
    } catch(const std::runtime_error &e) {
        // Property not found. Handle the error here.
    }

    // Write mesh file
    if(!OpenMesh::IO::read_mesh(mesh, outfile)) {
        std::cerr << "Error: Cannot write mesh to " << outfile << std::endl;
        return 1;
    }
}