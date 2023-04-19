import time
import ncnn
from ncnn.utils.objects import Detect_Object
from ncnn.utils import draw_detection_objects
from ncnn.model_zoo import get_model_list
import cv2


class YoloV3_Base:
    def __init__(
        self,
        tiny,
        param_path,
        bin_path,
        class_names,
        num_threads=1,
        use_gpu=False,
    ):
        target_size = 416 if tiny else 608
        self.target_size = target_size
        self.num_threads = num_threads
        self.use_gpu = use_gpu

        self.mean_vals = []
        self.norm_vals = [1 / 255.0, 1 / 255.0, 1 / 255.0]

        self.net = ncnn.Net()
        self.net.opt.use_vulkan_compute = self.use_gpu
        self.net.opt.num_threads = self.num_threads

        self.net.load_param(param_path)
        self.net.load_model(bin_path)

        self.class_names = class_names

    def __del__(self):
        self.net = None

    def __call__(self, img):
        img_h = img.shape[0]
        img_w = img.shape[1]

        mat_in = ncnn.Mat.from_pixels_resize(
            img,
            ncnn.Mat.PixelType.PIXEL_BGR2RGB,
            img.shape[1],
            img.shape[0],
            self.target_size,
            self.target_size,
        )
        mat_in.substract_mean_normalize(self.mean_vals, self.norm_vals)

        ex = self.net.create_extractor()
        ex.input("data", mat_in)

        ret, mat_out = ex.extract("output")

        objects = []

        # method 1, use ncnn.Mat.row to get the result, no memory copy
        for i in range(mat_out.h):
            values = mat_out.row(i)

            obj = Detect_Object()
            obj.label = values[0]
            obj.prob = values[1]
            obj.rect.x = values[2] * img_w
            obj.rect.y = values[3] * img_h
            obj.rect.w = values[4] * img_w - obj.rect.x
            obj.rect.h = values[5] * img_h - obj.rect.y

            objects.append(obj)

        # method 2, use ncnn.Mat->numpy.array to get the result, no memory copy too
        # out = np.array(mat_out)
        # for i in range(len(out)):
        #     values = out[i]
        #     obj = Detect_Object()
        #     obj.label = values[0]
        #     obj.prob = values[1]
        #     obj.x = values[2] * img_w
        #     obj.y = values[3] * img_h
        #     obj.w = values[4] * img_w - obj.x
        #     obj.h = values[5] * img_h - obj.y
        #     objects.append(obj)

        return objects


class YoloV3_Tiny(YoloV3_Base):
    def __init__(self, **kwargs):
        super(YoloV3_Tiny, self).__init__(tiny=True, **kwargs)


class YoloV3(YoloV3_Base):
    def __init__(self, **kwargs):
        super(YoloV3, self).__init__(tiny=False, **kwargs)


m = cv2.imread("000017.bmp")
net = YoloV3(
    param_path="yolov3-tiny_4000-opt.param",
    bin_path="yolov3-tiny-opt.bin",
    class_names=["", "exp", "hd", "jb"],
    num_threads=4,
    use_gpu=True,
)
s = time.time()
objects = net(m)
print(time.time() - s)
draw_detection_objects(m, net.class_names, objects)
