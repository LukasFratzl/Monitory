@tool
extends VideoStreamPlayer

@export var fit_to_screen: bool = true
@export var fit_to_screen_size: Vector2i = Vector2i(1920, 1080)

# Called when the node enters the scene tree for the first time.
func _ready():
	play()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if fit_to_screen:
		if not is_playing():
			play()
		_fit_to_screen(fit_to_screen_size)
	
func _fit_to_screen(texture_size):
	var viewport_size = get_viewport().get_visible_rect().size
	var scale_factor = max(float(viewport_size.x) / float(texture_size.x), float(viewport_size.y) / float(texture_size.y))
	var wanted_image_size = texture_size * scale_factor
	var aspect = float(texture_size.x) / float(texture_size.y)
	# portrait
	var wanted_size = Vector2(viewport_size.x, wanted_image_size.x)
	# landscape
	if aspect > 1.0:
		wanted_size = Vector2(wanted_image_size.y * aspect, wanted_image_size.y)
	if get_size() != wanted_size:
		set_size(wanted_size)
	position = get_viewport().get_visible_rect().get_center() - wanted_size * 0.5
	pass
