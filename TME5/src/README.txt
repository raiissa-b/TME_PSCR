Execution sans threads : 10 931 ms ( 10secondes) 

=> avec les threads on devrait pouvoir réussir à descendre jusqu'à 2 secondes environs (2000ms)
=> le but n'est pas d'avoir un thread/pixel on veut qu'un thread traite plusieurs pixels
    sinon la Queue (buffer circulaire) ne sert à rien en fait

1) La classe Queue 
-> va contenir les jobs , les taches à faire
comme en TD avec le isBlocking

2) dans le main on copie la partie calcul des deux boucles for imbriquées et on les met dans le run du main 
c'est ce que les threads doivent faire 
on met en attributs ce dont ils ont besoin ( pixels [=retour], scene, lights etc )
et on passera ça en argument à submit

class colorCalculJob : public Job {

	int x, y; 
	const Scene::screen_t &screen;
	Scene &scene;
	vector<Vec3D> &lights;
	Color * pixels;

public :
	colorCalculJob(int x, int y, const Scene::screen_t &screen,  Scene & scene,  vector<Vec3D> &lights, Color & pixels ): 
	x(x), y(y), screen(screen), scene(scene), lights(lights), pixels(&pixels) {}

	void run () {
		// le point de l'ecran par lequel passe ce rayon
			auto & screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon  ray(scene.getCameraPos(), screenPoint);

			int targetSphere = findClosestInter(scene, ray);

			if (targetSphere == -1) {
				// keep background color
				//continue ;
				return;//on termine si test réussi
				
			} else {
				const Sphere & obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
			Color & pixel = pixels[y*scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
			pixel = finalcolor;
			}
	}
	
};
//job avant barrier 



//job après barrier : 