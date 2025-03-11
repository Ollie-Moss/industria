#ifndef SSBO_H
#define SSBO_H

#include "Buffer.hpp"
#include "glad/glad.h"
#include <vector>

template <typename T>
struct SSBO {
	unsigned int ID;
	size_t size = 0;
	SSBO() {
		glCreateBuffers(1, &ID);
	}

	void Fill(std::vector<T> buf) {
		size = buf.size();
		glNamedBufferStorage(ID, buf.size() * sizeof(T), buf.data(), GL_DYNAMIC_STORAGE_BIT);
	}

	void Set(int index, T value) {
		glNamedBufferSubData(ID, index, sizeof(T), &value);
	}

	void Bind() {
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ID);
	}
};

#endif
