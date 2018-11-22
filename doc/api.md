

==========	[ NADIA OPERATING SYSTEM ] =======================

/nadia---------------------------
	/app-------------------------
		/do_login.c 	unavailable	// contient les routines d'identification et d'authentification des utilisateurs
		/do_shell.c 	unavailable	// contient les routines de configuration de la console et du shell(interpreteur
									   de command)
	/boot -----------------------
		/boot.asm 	// bootloader
	/doc-------------------------
		/api.md 	// contient la documentation de fichiers et des fonctions relatives a nadia
	/drivers---------------------
			 		unavailable // contient des routines de controles des peripheriques
	/fs--------------------------
					unavailable // contient des routines de construction, lecture, et d'ecriture sur les fichiers
	/include---------------------
		/fs.h 		unavailable // contient des definitions de fonctions et structure de donnees decrivant les fichiers
		/global.h 	// contient des variables et constantes globales
		/hd.h 		unavailable // contient des definitions de fonctions ur les acces disque et structure de donnees  
	 							   decrivant la structure du disque dure
	 	/io.h       // contient les routines entree et sortie
	 		inb(port, val)
	 		inw(port, val)
	 		inl(port, val)
	 		inbp(port, val)
	 		inwp(port, val)
	 		inlp(port, val)
	 		outb(port, val)
	 		outw(port, val)
	 		outl(port, val)
	 		outbp(port, val)
	 		outwp(port, val)
	 		outlp(port, val)
	 	/stdarg.h
	 	/stdio.h
	 	/string.h
	 	/symboles.h
	 	/types.h
	 /init------------------------
	 	/main.c 	// contient les routines de demarrage du systeme
	 /kernel----------------------
	 	/asm----------------------
	 		/segment.asm 	// contient les routines de chargement de la GDT et la IDT, de sauvergade et de 
	 						   restoration des registres, de chargement des interruptions materielles et les exceptions
	 	/include
	 		/