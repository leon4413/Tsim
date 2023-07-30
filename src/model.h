#ifndef MODEL
#define MODEL



/* Generate obj file from a heightmap
 * input:
 *  - heightmap pointer
 *  - x map dimension
 *  - y map dimension
 *  - filename
 *  outuput:
 *  - 1 Error
 *  - 0 Good
 *  */
int gen_obj_from_heightmap(int** heightmap, int x, int y, float scale, std::string filename);

#endif //MODEL
