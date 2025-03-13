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

    uint vertex1 = packedMeshData[index * 2];
    uint vertex2 = packedMeshData[index * 2 + 1];

    int x = int(vertex1) & 0xFFFF;
    int y = int(vertex1 >> 16) & 0xFFFF;
    int z = int(vertex2) & 0xFFFF;
    if ((x & 0x8000) != 0) {
        x = x | 0xFFFF0000;
    }
    if ((y & 0x8000) != 0) {
        y = y | 0xFFFF0000;
    }
    if ((z & 0x8000) != 0) {
        z = z | 0xFFFF0000;
    }
    int scaleX = int((vertex2 >> 16) & 0x00FFu);
    int scaleY = int((vertex2 >> 24) & 0x00FFu);

    vec3 position = vec3(x, y, z);
    vec3 scale = vec3(scaleX, scaleY, 1.0);

    position += facePositions[indices[currVertexID]] * scale;

    gl_Position = projection * vec4(position, 1.0);
    ourTexCoord = vec2(facePositions[indices[currVertexID]].xy);
}
