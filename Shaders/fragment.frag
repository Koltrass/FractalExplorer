#version 400 core
out vec4 FragColor;
uniform int iterations;
uniform double zoom;
uniform dvec2 offset;
void main()
{
    double cx = (gl_FragCoord.x/zoom + offset.x);
    double cy = (gl_FragCoord.y/zoom + offset.y);
    if (cx >-0.005 && cx < 0.005 && cy > -0.005 && cy < 0.005)
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        return;
    }
    if (cx >0.995 && cx < 1.005 && cy > -0.005 && cy < 0.005)
    {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        return;
    }
    if (cx > 790 && cx < 810)
    {
        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
        return;
    }
    if (cy > 440 && cy < 460)
    {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0);
        return;
    }
    double x = 0;
    double y = 0;
    double x2 = x * x;
    double y2 = y * y;
    int n = 0;
    while (x2 + y2 <= 4 && n < iterations)
    {
        y = 2*x*y +cy;
        x = x2-y2 +cx;
        x2 = x * x;
        y2 = y * y;
        n++;
    }
    if (n == iterations)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }
	FragColor = vec4(float(n)/iterations, float(n)/iterations, float(n)/iterations, 1.0);
}