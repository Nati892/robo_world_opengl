#pragma once
#include "stdafx.h"

class MatrixStack {
public:
    void push(const glm::mat4& matrix) {
        stack.push(matrix);
    }

    void pop() {
        if (!stack.empty()) {
            stack.pop();
        }
    }

    glm::mat4 top() const {
        if (stack.empty()) {
            return glm::mat4(1.0f); // Identity matrix
        }
        else {
            return stack.top();
        }
    }

private:
    std::stack<glm::mat4> stack;
};