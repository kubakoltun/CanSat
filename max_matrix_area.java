public static String max_matrix_area (String[] strArr) {
    int rows = strArr.length;
    int columns = strArr[0].length();
    int[][] dpMatrix = new int[rows][columns];
    int maxArea = 0;

    for(int i = 0; i < columns; i++) {
      dpMatrix[0][i] = strArr[0].charAt(i) - '0';
      maxArea = Math.max(maxArea, dpMatrix[0][i]);
    }

    for (int j = 1; j < rows; j++) {
      for (int g = 0; g < columns; g++) {
        if (strArr[j].charAt(g) == '1') {
          dpMatrix[j][g] = dpMatrix[j-1][g]+1;
        }
      }
      maxArea = Math.max(maxArea, calculateMaxArea(dpMatrix[j]));
    }

    return String.valueOf(maxArea);
  }

  public static int calculateMaxArea(int[] heights) {
    Stack<Integer> stack = new Stack<>();
    int maxArea = 0;
    int idx = 0;

    while (idx <= heights.length) {
      int currHeight = (idx == heights.length) ? 0 : heights[idx];
      if (stack.isEmpty() || currHeight >= heights[stack.peek()]) {
        stack.push(idx);
        idx++;
      } else {
        int topIdx = stack.pop();
        int width = stack.isEmpty() ? idx : idx - stack.peek() - 1;
        maxArea = Math.max(maxArea, heights[topIdx] * width); 
      }
    }
    
    return maxArea;
  }
