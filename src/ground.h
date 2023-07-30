#ifndef GROUND
#define GROUND

class ground {
	public:
		int** height_map;
		int dim_x;
		int dim_y;
		int dim_max;

		void gen_ground(int x, int y, int max);
		void print_ground();
		void random_fill();
		void filter_pass();
		void render();
		void renderf();
};

class planet {
	public:
		/* Variables */
		float pos[3];
		int phy; // 0 to 2*PI
		int theta; // 0 to PI

		float** height_map;

		/* functions */
		void gen_surface(int p, int t, int f_pass, int cutoff, int z_max, int z_min);
		void print_surface();
		void random_fill(int z_max, int z_min);
		void filter_pass();
		void cut_off(float cut);
		void render();
};

#endif //GROUND
