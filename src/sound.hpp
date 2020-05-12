void coin_sound()//claire
{
    SDL_QueueAudio(device_coin, wav_buffer[1], wav_length[1]);
    SDL_PauseAudioDevice(device_coin, 0);
}
void hit_sound()//claire
{
    SDL_QueueAudio(device_enemy, wav_buffer[0], wav_length[0]);
    SDL_PauseAudioDevice(device_enemy, 0);
}