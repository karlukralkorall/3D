#include <opencv2/opencv.hpp>

#define WIDTH 1000
#define HEIGHT 1000
#define BLACK cv::Scalar(0,0,0)
#define WHITE cv::Scalar(255,255,255)
#define GRAY cv::Scalar(150,150,150)
#define GREEN cv::Scalar(0,255,0)
#define BLUE cv::Scalar(255,0,0)
#define RED cv::Scalar(0,0,255)
#define POW2(x) ((x)*(x))
#define TO_RAD(x) ((CV_PI/180)*x)

class Space3D
{
private:
	cv::Point3f center_m;
	cv::Point3f ox_m;
	cv::Point3f oy_m;
	cv::Point3f oz_m;
public:
	Space3D(): ox_m(100,0,0), oy_m(0,100,0), oz_m(0,0,100), center_m(500,500,0)
	{}
	~Space3D()
	{}

	void axesRender(cv::Mat& img)
	{
		img.setTo(GRAY);
		cv::line(img, cv::Point(center_m.x, center_m.y), cv::Point(center_m.x + ox_m.x, center_m.y - ox_m.y), BLUE);
		cv::putText(img, "X", cv::Point(center_m.x + ox_m.x, center_m.y - ox_m.y),1,1,BLUE);

		cv::line(img, cv::Point(center_m.x, center_m.y), cv::Point(center_m.x + oy_m.x, center_m.y - oy_m.y), BLUE);
		cv::putText(img, "Y", cv::Point(center_m.x + oy_m.x, center_m.y - oy_m.y), 1, 1, BLUE);

		cv::line(img, cv::Point(center_m.x, center_m.y), cv::Point(center_m.x + oz_m.x, center_m.y - oz_m.y), BLUE);
		cv::putText(img, "Z", cv::Point(center_m.x + oz_m.x, center_m.y - oz_m.y), 1, 1, BLUE);
	}

	void pointRender(cv::Mat& img, cv::Point3f point, cv::Scalar color)
	{
		//float x = sqrtf(POW2(point.x*ox_m.x) + POW2(point.y*oy_m.x) + POW2(point.z*oz_m.x));
		//float y = sqrtf(POW2(point.x * ox_m.y) + POW2(point.y * oy_m.y) + POW2(point.z * oz_m.y));
		float mat[3][3] = { {ox_m.x,oy_m.x,oz_m.x},
							{ox_m.y,oy_m.y,oz_m.y},
							{ox_m.z,oy_m.z,oz_m.z} };

		float pt[3] = {point.x,point.y,point.z};

		float result[3];
		result[0] = mat[0][0] * pt[0] + mat[0][1] * pt[1] + mat[0][2] * pt[2];
		result[1] = mat[1][0] * pt[0] + mat[1][1] * pt[1] + mat[1][2] * pt[2];
		result[2] = mat[2][0] * pt[0] + mat[2][1] * pt[1] + mat[2][2] * pt[2];

		//std::cout << "x = " << x << " y = " << y << '\n';
		cv::circle(img, cv::Point(center_m.x + result[0], center_m.y - result[1]), 2, color, -1);
	}

	void changeX(int alfa)
	{
		float mat[3][3] = { {1,                 0,                        0},
							{0, cosf(TO_RAD(alfa)), (-1) * sinf(TO_RAD(alfa))},
							{0, sinf(TO_RAD(alfa)),      cosf(TO_RAD(alfa))} };
		float coord[3][3] = { {ox_m.x, oy_m.x, oz_m.x},
								{ox_m.y, oy_m.y, oz_m.y},
								{ox_m.z, oy_m.z, oz_m.z} };


		float result[3][3];
		result[0][0] = mat[0][0] * coord[0][0] + mat[0][1] * coord[1][0] + mat[0][2] * coord[2][0];
		result[1][0] = mat[1][0] * coord[0][0] + mat[1][1] * coord[1][0] + mat[1][2] * coord[2][0];
		result[2][0] = mat[2][0] * coord[0][0] + mat[2][1] * coord[1][0] + mat[2][2] * coord[2][0];

		result[0][1] = mat[0][0] * coord[0][1] + mat[0][1] * coord[1][1] + mat[0][2] * coord[2][1];
		result[1][1] = mat[1][0] * coord[0][1] + mat[1][1] * coord[1][1] + mat[1][2] * coord[2][1];
		result[2][1] = mat[2][0] * coord[0][1] + mat[2][1] * coord[1][1] + mat[2][2] * coord[2][1];

		result[0][2] = mat[0][0] * coord[0][2] + mat[0][1] * coord[1][2] + mat[0][2] * coord[2][2];
		result[1][2] = mat[1][0] * coord[0][2] + mat[1][1] * coord[1][2] + mat[1][2] * coord[2][2];
		result[2][2] = mat[2][0] * coord[0][2] + mat[2][1] * coord[1][2] + mat[2][2] * coord[2][2];

		ox_m.x = result[0][0];
		ox_m.y = result[1][0];
		ox_m.z = result[2][0];

		oy_m.x = result[0][1];
		oy_m.y = result[1][1];
		oy_m.z = result[2][1];

		oz_m.x = result[0][2];
		oz_m.y = result[1][2];
		oz_m.z = result[2][2];
	}

	void changeY(int alfa)
	{
		float mat[3][3] = { {       cosf(TO_RAD(alfa)), 0, sinf(TO_RAD(alfa))},
							{                        0, 1,                  0},
							{(-1) * sinf(TO_RAD(alfa)), 0, cosf(TO_RAD(alfa))} };
		float coord[3][3] = { {ox_m.x, oy_m.x, oz_m.x},
								{ox_m.y, oy_m.y, oz_m.y},
								{ox_m.z, oy_m.z, oz_m.z} };


		float result[3][3];
		result[0][0] = mat[0][0] * coord[0][0] + mat[0][1] * coord[1][0] + mat[0][2] * coord[2][0];
		result[1][0] = mat[1][0] * coord[0][0] + mat[1][1] * coord[1][0] + mat[1][2] * coord[2][0];
		result[2][0] = mat[2][0] * coord[0][0] + mat[2][1] * coord[1][0] + mat[2][2] * coord[2][0];

		result[0][1] = mat[0][0] * coord[0][1] + mat[0][1] * coord[1][1] + mat[0][2] * coord[2][1];
		result[1][1] = mat[1][0] * coord[0][1] + mat[1][1] * coord[1][1] + mat[1][2] * coord[2][1];
		result[2][1] = mat[2][0] * coord[0][1] + mat[2][1] * coord[1][1] + mat[2][2] * coord[2][1];

		result[0][2] = mat[0][0] * coord[0][2] + mat[0][1] * coord[1][2] + mat[0][2] * coord[2][2];
		result[1][2] = mat[1][0] * coord[0][2] + mat[1][1] * coord[1][2] + mat[1][2] * coord[2][2];
		result[2][2] = mat[2][0] * coord[0][2] + mat[2][1] * coord[1][2] + mat[2][2] * coord[2][2];

		ox_m.x = result[0][0];
		ox_m.y = result[1][0];
		ox_m.z = result[2][0];

		oy_m.x = result[0][1];
		oy_m.y = result[1][1];
		oy_m.z = result[2][1];

		oz_m.x = result[0][2];
		oz_m.y = result[1][2];
		oz_m.z = result[2][2];
	}

	void changeZ(int alfa)
	{
		float mat[3][3] = { {cosf(TO_RAD(alfa)), (-1) * sinf(TO_RAD(alfa)), 0},
							{sinf(TO_RAD(alfa)),        cosf(TO_RAD(alfa)), 0},
							{                 0,                         0, 1} };
		float coord[3][3] = { {ox_m.x, oy_m.x, oz_m.x},
								{ox_m.y, oy_m.y, oz_m.y},
								{ox_m.z, oy_m.z, oz_m.z} };


		float result[3][3];
		result[0][0] = mat[0][0] * coord[0][0] + mat[0][1] * coord[1][0] + mat[0][2] * coord[2][0];
		result[1][0] = mat[1][0] * coord[0][0] + mat[1][1] * coord[1][0] + mat[1][2] * coord[2][0];
		result[2][0] = mat[2][0] * coord[0][0] + mat[2][1] * coord[1][0] + mat[2][2] * coord[2][0];

		result[0][1] = mat[0][0] * coord[0][1] + mat[0][1] * coord[1][1] + mat[0][2] * coord[2][1];
		result[1][1] = mat[1][0] * coord[0][1] + mat[1][1] * coord[1][1] + mat[1][2] * coord[2][1];
		result[2][1] = mat[2][0] * coord[0][1] + mat[2][1] * coord[1][1] + mat[2][2] * coord[2][1];

		result[0][2] = mat[0][0] * coord[0][2] + mat[0][1] * coord[1][2] + mat[0][2] * coord[2][2];
		result[1][2] = mat[1][0] * coord[0][2] + mat[1][1] * coord[1][2] + mat[1][2] * coord[2][2];
		result[2][2] = mat[2][0] * coord[0][2] + mat[2][1] * coord[1][2] + mat[2][2] * coord[2][2];

		ox_m.x = result[0][0];
		ox_m.y = result[1][0];
		ox_m.z = result[2][0];

		oy_m.x = result[0][1];
		oy_m.y = result[1][1];
		oy_m.z = result[2][1];

		oz_m.x = result[0][2];
		oz_m.y = result[1][2];
		oz_m.z = result[2][2];
	}
};
int main()
{
	cv::namedWindow("output", cv::WINDOW_AUTOSIZE);
	cv::Mat outputImage(HEIGHT, WIDTH, CV_8UC3);
	outputImage.setTo(GRAY);
	Space3D sp;
	int X = 0;
	int Y = 0;
	int Z = 0;
	while (true)
	{
		sp.axesRender(outputImage);
		cv::putText(outputImage, "X: " + std::to_string(X), cv::Point(30, 30), 1, 1, RED);
		sp.pointRender(outputImage, cv::Point3f(0.5, 0.5, 0.5), RED);
		cv::imshow("output", outputImage);
		int key = cv::waitKey(1);
		if (key == 27) goto end;
		if (key == 113) { X = 10; sp.changeX(X); }
		if (key == 119) { X = -10; sp.changeX(X); }

		if (key == 97) { Y = 10; sp.changeY(Y); }
		if (key == 115) { Y = -10; sp.changeY(Y); }

		if (key == 122) { Z  = 10; sp.changeZ(Z); }
		if (key == 120) { Z = -10; sp.changeZ(Z); }

		
	}
	end:
	return 0;
}