import random

import qrcode
import numpy as np
from PIL import Image


def create_qr_code(data, mask_pattern=None) -> np.array:
    qr = qrcode.QRCode(
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=0,
        mask_pattern=mask_pattern,
    )
    qr.add_data(data)
    qr.make()

    return np.array(qr.get_matrix())


def extract_format_info(qr_array: np.array) -> dict[str, np.array]:
    size = qr_array.shape[0]

    format_info = {
        # 9th row (index 8), 8 bits
        "top-left-horizontal": qr_array[8, 0:8],
        # 9th column (index 8), 9 bits
        "top-left-vertical": qr_array[0:9, 8],
        # 9th row (index 8), last 8 bits
        "top-right-horizontal": qr_array[8, size - 8:size],
        # 9th column (index 8), last 7 bits
        "bottom-left-vertical": qr_array[size - 7:size, 8],
    }

    return format_info


def replace_format_info(qr_array: np.array, new_format_info: dict[str, np.array]):
    size = qr_array.shape[0]

    qr_array[8, 0:8] = new_format_info["top-left-horizontal"]
    qr_array[0:9, 8] = new_format_info["top-left-vertical"]
    qr_array[8, size - 8:size] = new_format_info["top-right-horizontal"]
    qr_array[size - 7:size, 8] = new_format_info["bottom-left-vertical"]

    return qr_array


def random_other_mask(flag_mask_pattern: int) -> int:
    numbers = [x for x in range(8) if x != flag_mask_pattern]
    return random.choice(numbers)


def create_broken(flag: str, correct_mask: int):
    # create the correct QR code
    correct_qr = create_qr_code(flag, mask_pattern=correct_mask)
    correct_qr_format_info = extract_format_info(correct_qr)
    correct_qr_img = Image.fromarray(np.invert(correct_qr))
    correct_qr_img.save("correct_qr.png")

    # create a temporary QR code to extract the format info
    temporary_qr = create_qr_code(flag, mask_pattern=random_other_mask(correct_mask))
    temporary_qr_format_info = extract_format_info(temporary_qr)

    # apply wrong format info to the correct QR code
    broken_qr = replace_format_info(correct_qr, temporary_qr_format_info)
    broken_qr_format_info = extract_format_info(broken_qr)

    # sanity check
    for key in correct_qr_format_info:
        assert np.array_equal(correct_qr_format_info[key], broken_qr_format_info[key])

    broken_qr_img = Image.fromarray(np.invert(broken_qr))
    broken_qr_img.save("broken_qr.png")


if __name__ == "__main__":
    create_broken("zeroday{unm4sk1ng_th3_m4g1c}", correct_mask=6)
