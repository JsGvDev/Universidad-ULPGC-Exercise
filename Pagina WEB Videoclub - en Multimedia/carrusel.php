	<div class="categorias" id="categorias">
		<div id="image_carousel">
			<div id="foo2">
				<?php
					if($con=mysql_connect(HOST,USER,PASS)){
						mysql_select_db(videoclub1080p,$con);
						mysql_query("SET NAMES 'utf8'");
						
						$consulta="(SELECT * FROM categorias)";
						if($result=mysql_query($consulta)){ 
							while(($fila=mysql_fetch_array($result))){							
								echo '<div><a href="http://localhost/videoclub/categorias.php?categoria='.$fila['slugcategorias'].'"><img src='.$fila[imagencat].' width=100 height=100 /><span>'.$fila['categoria'].'</span></a></div>';
							}
						}
					}
				?>
			</div>
			<div class="clearfix"></div>
			<a class="prev" id="foo2_prev" href="#"><span>prev</span></a>
			<a class="next" id="foo2_next" href="#"><span>next</span></a>
			<div class="pagination" id="foo2_pag"></div>
		</div> <!-- /image_carousel -->
	</div>	