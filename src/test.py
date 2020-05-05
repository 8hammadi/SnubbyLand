import requests

from django.http import StreamingHttpResponse

def api_gateway_portal(request, path=''):
    url = 'http://some.ip.address/%s?api_key=12345678901234567890' % (path,)
    r = requests.get(url, stream=True)

    response = StreamingHttpResponse(
        (chunk for chunk in r.iter_content(512 * 1024)),
        content_type='application/json')

    return response