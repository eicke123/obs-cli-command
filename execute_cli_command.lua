obs = obslua
settings = {}

function script_description()
	return [[
Execute a CLI command whenever recording/streaming starts/stops.
]]
end

function script_properties()
	local props = obs.obs_properties_create()

	obs.obs_properties_add_bool(props, "stream_start", "Execute when streaming started")
	obs.obs_properties_add_text(props, "stream_start_command", "Stream started command", obs.OBS_TEXT_DEFAULT)
	
	obs.obs_properties_add_bool(props, "stream_stop", "Execute when recording stoped")
	obs.obs_properties_add_text(props, "stream_stop_command", "Stream stoped command", obs.OBS_TEXT_DEFAULT)
	
	obs.obs_properties_add_bool(props, "rec_start", "Execute when recording started")
	obs.obs_properties_add_text(props, "rec_start_command", "Rec started command", obs.OBS_TEXT_DEFAULT)
	
	obs.obs_properties_add_bool(props, "rec_stop", "Execute when recording stoped")
	obs.obs_properties_add_text(props, "rec_stop_command", "Rec stoped command", obs.OBS_TEXT_DEFAULT)
	
	return props
end

function script_update(_settings)	
	settings = _settings
end

function script_load(settings)
	settings = _settings
	obs.obs_frontend_add_event_callback(handle_event)
end

function handle_event(event)
	if event == obs.OBS_FRONTEND_EVENT_RECORDING_STARTED then
		local enabled = obs.obs_data_get_bool(settings, "rec_start" )
		if enabled then
			local command = obs.obs_data_get_string(settings, "rec_start_command")
		os.execute(command)	
		end
	end

	if event == obs.OBS_FRONTEND_EVENT_RECORDING_STOPPING then
		local enabled = obs.obs_data_get_bool(settings, "rec_stop" )
		if enabled then
			local command = obs.obs_data_get_string(settings, "rec_stop_command")
		os.execute(command)	
		end
	end
	
end