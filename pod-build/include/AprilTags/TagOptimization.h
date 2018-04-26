namespace AprilTags{
  class TagOptimization {
      public:
	void set(double TIME, int TAGID, double x, double y, double PITCH, double ROLL, double YAW);
	void optimize();
	void print();
      private:
	int count;
	double time;
	int tagID;
	double X, Y, Z; //Meters
	double pitch, roll, yaw; //Radians
	double QR_X, QR_Y; // Meters
	double QR_Z = 8.1; //Meters 
	double CAMERA_X, CAMERA_Y, CAMERA_Z; //Meters
	double QR_X_Rot, QR_Y_Rot;
	double coordinates[9][2] = { { 4.117,1.217 },{ 1.446,3.442 },{ 4.141,5.089 },{ 0,0 },{ 0,0 },{ 0,-.7 },{ 0,1 },{ 0,0 },{ 0,0 } };
  };
}
