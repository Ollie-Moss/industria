#version 430 core

layout(std430, binding = 0) readonly buffer vertexPullBuffer
{
    uint packedMeshData[]; // Contains packed data for our vertices
};

out vec2 ourTexCoord;

// Offsets for our vertices drawing this face
const vec3 facePositions[4] = vec3[4](
        vec3(0.0, 0.0, 0.0),
        vec3(0.0, 1.0, 0.0),
        vec3(1.0, 1.0, 0.0),
        vec3(1.0, 0.0, 0.0)
    );

// Winding order to access the face positions
int indices[6] = {
        0,
        1,
        2,
        3,
        0,
        2
    };

uniform mat4 projection;

void main()
{
    int index = gl_VertexID / 6;
    int currVertexID = gl_VertexID % 6;

    // Unpack vertices (same logic as C++ code)
    uint vertex1 = packedMeshData[index * 2];
    uint vertex2 = packedMeshData[index * 2 + 1];

    // Unpack position (x, y, z) from vertex1 and vertex2
    int x = int(vertex1 & 0xFFFFu); // Cast to uint before using & operation
    int y = int((vertex1 >> 16u) & 0xFFFFu); // Cast to uint before using & operation
    int z = int(vertex2 & 0xFFFFu); // Cast to uint before using & operation

    if ((int(x) & int(0x8000)) != 0) {
        x -= 65536; // Two's complement signed value for x
    }
    if ((int(y) & int(0x8000)) != 0) {
        y -= 65536; // Two's complement signed value for y
    }
    if ((int(z) & int(0x8000)) != 0) {
        z -= 65536; // Two's complement signed value for z
    }

    // Unpack scale (scaleX, scaleY, scaleZ) from vertex2 and vertex3
    int scaleX = int((vertex2 >> 16) & 0x00FFu); // Cast to uint before using & operation
    int scaleY = int((vertex2 >> 24) & 0x00FFu); // Cast to uint before using & operation
    if ((int(scaleX) & int(0x0080)) != 0) {
        scaleX -= 255;
    }
    if ((int(scaleY) & int(0x0080)) != 0) {
        scaleY -= 255;
    }

    // Create position and scale vectors
    vec3 position = vec3(x, y, z);
    vec3 scale = vec3(scaleX, scaleY, 1.0);

    // Apply the offsets for our face so we can form the 2 triangles
    position += facePositions[indices[currVertexID]] * scale;

    gl_Position = projection * vec4(position, 1.0);
    ourTexCoord = vec2(facePositions[indices[currVertexID]].xy);
}
