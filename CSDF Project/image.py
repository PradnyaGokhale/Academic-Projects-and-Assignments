from PIL import Image, ImageChops, ImageEnhance, ImageDraw
from PIL.ExifTags import TAGS, GPSTAGS
import hashlib
import cv2
import numpy as np
import matplotlib.pyplot as plt
from scipy import ndimage

# Function to extract and parse GPS data from EXIF metadata
def extract_gps_data(exif_data):
    gps_info = {}
    for tag, value in exif_data.items():
        tag_name = TAGS.get(tag, tag)
        if tag_name == "GPSInfo":
            for t in value:
                sub_tag_name = GPSTAGS.get(t, t)
                gps_info[sub_tag_name] = value[t]
            break
    return gps_info

# Metadata extraction function
def extract_metadata(image_path):
    try:
        image = Image.open(image_path)
        exif_data = image._getexif()  # Extract EXIF data
        if not exif_data:
            print("No EXIF data found.")
            return None

        metadata = {}
        software_used = None
        for tag, value in exif_data.items():
            tag_name = TAGS.get(tag, tag)
            metadata[tag_name] = value
            if tag_name == 'Software':
                software_used = value
        if software_used:
            print(f"Image may have been edited using: {software_used}")
        else:
            print("No editing software detected in metadata.")
        return metadata
    except Exception as e:
        print(f"Error extracting metadata: {e}")
        return None

# Generate image hash values (MD5 and SHA-256)
def generate_image_hash(image_path):
    try:
        with open(image_path, "rb") as img_file:
            img_data = img_file.read()
            md5_hash = hashlib.md5(img_data).hexdigest()
            sha256_hash = hashlib.sha256(img_data).hexdigest()
        return {"MD5": md5_hash, "SHA-256": sha256_hash}
    except Exception as e:
        print(f"Error generating hash: {e}")
        return None

def error_level_analysis(image_path, output_path, quality=90, threshold=50, resize_factor=0.5):
    try:
        original_image = Image.open(image_path)
        
        # Resize image for faster processing
        new_size = (int(original_image.width * resize_factor), int(original_image.height * resize_factor))
        original_image = original_image.resize(new_size, Image.LANCZOS)

        # Save the image at a reduced quality
        resaved_image_path = "resaved_image.jpg"
        original_image.save(resaved_image_path, 'JPEG', quality=quality)
        
        resaved_image = Image.open(resaved_image_path)
        
        # Perform Error Level Analysis by subtracting the images
        ela_image = ImageChops.difference(original_image, resaved_image)
        
        # Enhance the differences
        extrema = ela_image.getextrema()
        if isinstance(extrema[0], tuple):  # Handle multi-band images (e.g., RGB)
            extrema = [max(e) for e in extrema]
        max_diff = max(extrema)  # Extract the maximum pixel value
        
        if max_diff == 0:
            print("No differences detected for ELA.")
            return
        
        scale = 255.0 / max_diff  # Scale differences
        ela_image = ImageEnhance.Brightness(ela_image).enhance(scale)
        
        # Convert ELA image to grayscale for easier thresholding
        ela_image_gray = ela_image.convert('L')
        ela_data = np.array(ela_image_gray)
        
        # Apply threshold to detect significant differences
        mask = ela_data > threshold  # True for values above the threshold
        
        # Highlight manipulated areas by drawing bounding boxes
        draw = ImageDraw.Draw(ela_image)
        labeled, num_objects = ndimage.label(mask)  # Label connected regions
        for i in range(1, num_objects + 1):
            region = np.where(labeled == i)
            ymin, ymax = np.min(region[0]), np.max(region[0])
            xmin, xmax = np.min(region[1]), np.max(region[1])
            draw.rectangle([xmin, ymin, xmax, ymax], outline="red", width=2)  # Draw red bounding boxes
        
        # Save the ELA image with highlighted manipulations
        ela_image.save(output_path)
        print(f"ELA image with highlighted manipulation saved at: {output_path}")

    except Exception as e:
        print(f"Error performing ELA: {e}")

# Optimize noise analysis function
def analyze_noise(image_path, roi=None, resize_factor=0.5):
    try:
        image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
        if image is None:
            print("Image could not be opened.")
            return None

        # Resize image for faster processing
        new_size = (int(image.shape[1] * resize_factor), int(image.shape[0] * resize_factor))
        image = cv2.resize(image, new_size, interpolation=cv2.INTER_LANCZOS4)

        if roi:  # Crop the image to the region of interest (ROI)
            x, y, w, h = roi
            image = image[y:y+h, x:x+w]

        # Apply Fourier Transform to detect noise patterns
        f_transform = np.fft.fft2(image)
        f_transform_shifted = np.fft.fftshift(f_transform)
        magnitude_spectrum = 20 * np.log(np.abs(f_transform_shifted) + 1e-10)  # Avoid log(0)
        
        # Plot and analyze noise pattern
        plt.figure(figsize=(6, 6))
        plt.title("Fourier Transform (Noise Pattern)")
        plt.imshow(magnitude_spectrum, cmap='gray')
        plt.axis('off')  # Hide axis
        plt.show()

        return magnitude_spectrum
    except Exception as e:
        print(f"Error analyzing noise: {e}")
        return None

# Main execution flow
if __name__ == "__main__":
    image_path = './collage.jpg'  # Change this to your image file path

    # Extract metadata and check for editing software
    print("\n---- Extracting Metadata ----")
    metadata = extract_metadata(image_path)

    # Generate and print image hashes
    print("\n---- Generating Image Hashes ----")
    image_hash = generate_image_hash(image_path)
    if image_hash:
        print("MD5 Hash:", image_hash["MD5"])
        print("SHA-256 Hash:", image_hash["SHA-256"])

    # Perform Error Level Analysis (ELA) and highlight manipulation
    print("\n---- Performing Error Level Analysis (ELA) ----")
    error_level_analysis(image_path, "ela_result.jpg")

    # Perform Noise Pattern Analysis
    print("\n---- Performing Noise Pattern Analysis ----")
    analyze_noise(image_path)
