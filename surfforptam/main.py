import cv2

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

if __name__ == '__main__':
    cap = cv2.VideoCapture(0)
    while 1:
        ret, img = cap.read()
        tmp = params_from_image(img)
        cv2.imshow('', img)
        cv2.waitKey(1) 
