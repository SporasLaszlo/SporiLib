__kernel void warpPerspective_2D_8UC3(__global const float *HInv, int imgInWidth, int imgInHeight, __global const uchar *imgIn, int imgOutWidth, int imgOutHeight, __global uchar *imgOut)
{
	int xOut = get_global_id(0);
	int yOut = get_global_id(1);

	if ((xOut < imgOutWidth) && (yOut < imgOutHeight))
	{

		float xFrom = (float)xOut * HInv[0] + (float)yOut * HInv[1] + (float)1 * HInv[2];
		float yFrom = (float)xOut * HInv[3] + (float)yOut * HInv[4] + (float)1 * HInv[5];
		float zFrom = (float)xOut * HInv[6] + (float)yOut * HInv[7] + (float)1 * HInv[8];

		xFrom = xFrom / zFrom;
		yFrom = yFrom / zFrom;

		int xIn = (int)xFrom;
		int yIn = (int)yFrom;

		if ((xIn > -1) && (yIn > -1) && (xIn < imgInWidth) && (yIn < imgInHeight))
		{
			int inPos = 3 * imgInWidth * yIn + 3 * xIn;
			int outPos = 3 * imgOutWidth * yOut + 3 * xOut;

			imgOut[outPos] = imgIn[inPos];
			imgOut[outPos + 1] = imgIn[inPos + 1];
			imgOut[outPos + 2] = imgIn[inPos + 2];
		}
		else
		{
			int outPos = 3 * imgOutWidth * yOut + 3 * xOut;

			imgOut[outPos] = 0;
			imgOut[outPos + 1] = 0;
			imgOut[outPos + 2] = 0;
		}
	}
}