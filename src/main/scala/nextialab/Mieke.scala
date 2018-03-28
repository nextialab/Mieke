package nextialab

import scalafx.Includes._
import scalafx.application.JFXApp
import scalafx.scene.{Group, Scene}
import scalafx.scene.canvas.Canvas
import scalafx.scene.paint.Color

object Mieke extends JFXApp {

	val canvas = new Canvas(600, 480)
	val rootPane = new Group
	val context = canvas.graphicsContext2D
	var running = true
	val ticks = new Thread(new Runnable {
		def run() {
			while (running) {
				Thread.sleep(100);
				if (context.fill == Color.Blue) {
					context.fill = Color.Red
				} else {
					context.fill = Color.Blue
				}
				context.fillRect(0, 0, canvas.width.get, canvas.height.get)
			}
			println("Closing thread")
		}
	})
	rootPane.children = List(canvas)
	stage = new JFXApp.PrimaryStage {
		title.value = "Mieke"
		scene = new Scene(600, 480) {
			root = rootPane
			onCloseRequest = handle {
				running = false
				ticks.join
			}
		}
	}
	ticks.start

}