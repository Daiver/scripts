import numpy as np
import cv2
from functools import partial

help_message = '''SURF image match 

USAGE: findobj.py [ <image1> <image2> ]
'''

FLANN_INDEX_KDTREE = 1  # bug: flann enums are missing
flann_params = dict(algorithm = FLANN_INDEX_KDTREE,
                    trees = 4)

def match_flann(desc1, desc2, r_threshold = 0.6):
    flann = cv2.flann_Index(desc2, flann_params)
    idx2, dist = flann.knnSearch(desc1, 2, params = {}) # bug: need to provide empty dict
    mask = dist[:,0] / dist[:,1] < r_threshold
    idx1 = np.arange(len(desc1))
    pairs = np.int32( zip(idx1, idx2[:,0]) )
    return pairs[mask]

def draw_match(img1, img2, p1, p2, status = None, H = None):
    h1, w1 = img1.shape[:2]
    h2, w2 = img2.shape[:2]
    vis = np.zeros((max(h1, h2), w1+w2), np.uint8)
    vis[:h1, :w1] = img1
    vis[:h2, w1:w1+w2] = img2
    vis = cv2.cvtColor(vis, cv2.COLOR_GRAY2BGR)

    if H is not None:
        corners = np.float32([[0, 0], [w1, 0], [w1, h1], [0, h1]])
        corners = np.int32( cv2.perspectiveTransform(corners.reshape(1, -1, 2), H).reshape(-1, 2) + (w1, 0) )
        #cv2.polylines(vis, [corners], True, (255, 255, 255))
    
    if status is None:
        status = np.ones(len(p1), np.bool_)
    green = (0, 255, 0)
    red = (0, 0, 255)
    for (x1, y1), (x2, y2), inlier in zip(np.int32(p1), np.int32(p2), status):
        col = [red, green][inlier]
        if inlier:
            cv2.line(vis, (x1, y1), (x2+w1, y2), col)
            cv2.circle(vis, (x1, y1), 2, col, -1)
            cv2.circle(vis, (x2+w1, y2), 2, col, -1)
        else:
            r = 2
            thickness = 3
            cv2.line(vis, (x1-r, y1-r), (x1+r, y1+r), col, thickness)
            cv2.line(vis, (x1-r, y1+r), (x1+r, y1-r), col, thickness)
            cv2.line(vis, (x2+w1-r, y2-r), (x2+w1+r, y2+r), col, thickness)
            cv2.line(vis, (x2+w1-r, y2+r), (x2+w1+r, y2-r), col, thickness)
    return vis

def params_from_image(img, surf=None):
    if surf == None:surf = cv2.SURF(1000)
    kp, desc = surf.detect(img, None, False)
    desc.shape = (-1, surf.descriptorSize())
    return {'img':img, 'kp':kp, 'desc':desc}

def template_match(params_orig, params_template):
    img1, kp1, desc1 = params_orig['img'], params_orig['kp'], params_orig['desc']
    img2, kp2, desc2 = params_template['img'], params_template['kp'], params_template['desc']

    r_threshold = 0.55
    m = match_flann(desc1, desc2, r_threshold)
    dtmp = {}
    for i, j in m: dtmp[j] = i
    m = [[i, j] for j, i in dtmp.iteritems()]
    matched_p1 = np.array([kp1[i].pt for i, j in m])
    matched_p2 = np.array([kp2[j].pt for i, j in m])
    try:
        H, status = cv2.findHomography(matched_p1, matched_p2, cv2.RANSAC, 5.0)
    except:
        H = None
        status = None
    vis_flann = draw_match(img1, img2, matched_p1, matched_p2, status, H)
    return vis_flann, status

if __name__ == '__main__':
    import sys
    try: fn1, fn2 = sys.argv[1:3]
    except:
        fn1 = 'img.jpg'
        fn2 = 'template.jpg'
        print help_message

    img1 = cv2.imread(fn1, 0)
    img2 = cv2.imread(fn2, 0)
    camCap = cv2.VideoCapture(0)
    is_ready = False
    template = None
    i = 0
    while 1:
        i += 1
        ret, frame = camCap.read()
        key = cv2.waitKey(1) % 0x100
        is_ready = key == 120
        if is_ready:
            template = frame
        if template != None and i % 5 == 0:
            surf = cv2.SURF(1000)
            pr1 = params_from_image(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY))#img1)
            pr2 = params_from_image(cv2.cvtColor(template, cv2.COLOR_BGR2GRAY))#img2)
            print 'img1 - %d features, img2 - %d features' % (len(pr1['kp']), len(pr2['kp']))
            vis_flann, status = template_match(pr1, pr2)
            print 'flann match:',
            if status != None:
                print '%d / %d  inliers/matched' % (np.sum(status), len(status))
            cv2.imshow('find_obj SURF flann', vis_flann)
        else:
            cv2.imshow('', frame)

    surf = cv2.SURF(1000)
    pr1 = params_from_image(img1)
    pr2 = params_from_image(img2)
    print 'img1 - %d features, img2 - %d features' % (len(pr1['kp']), len(pr2['kp']))
    vis_flann, status = template_match(pr1, pr2)
    print 'flann match:',
    if status != None:
        print '%d / %d  inliers/matched' % (np.sum(status), len(status))
    cv2.imshow('find_obj SURF flann', vis_flann)
    cv2.waitKey()
