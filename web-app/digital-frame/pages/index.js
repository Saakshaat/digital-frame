import { useRef, useState } from "react";

import Head from "next/head";
import styles from "../styles/Home.module.css";

const ping_url = `http://pictureFrame.local/ping`;
const img_upload = `http://pictureFrame.local/img_data`;

export async function getStaticProps(context) {
  var status = {};
  try {
    const res = await fetch(ping_url, { mode: "cors", method: "GET" });

    status =
      res.status == 200
        ? { value: "Active", color: "#18A558" }
        : { value: "Unavailable", color: "#750000" };
  } catch (err) {
    status = { value: "Unavailable", color: "#750000" };
  }
  if (status.length === 0) status = "Unavailable";

  return {
    props: {
      status,
    },
  };
}

export default function Home({ status }) {
  var img_uri = useRef("");

  const [responseGood, setResponse] = useState(null);

  const validImageUri = async (imageUri) =>
    ["jpeg", "jpg", "png"].includes(
      imageUri.substring(imageUri.lastIndexOf(".") + 1)
    );

  const handleSubmit = async (e) => {
    try {
      if (img_uri.current.value.length === 0) {
        return;
      }

      if (!validImageUri(img_uri.current.value)) {
        setResponse("Please submit image URI for a .png, .jpg or .jpeg");
      }
      const res = await fetch(img_upload, {
        method: "POST",
        mode: "cors",
        headers: { "Content-Type": "text/plain" },
        body: img_uri.current.value,
      }).then((res) => {
        setResponse("Uploaded Successfully");
        console.log(res);
        if (res.status === 200) {
          setResponse("Uploaded Successfully");
        } else {
          setResponse("Uploaded Failed");
        }
      });
    } catch (err) {
      console.error(err);
    }
  };
  return (
    <div className={styles.container}>
      <Head>
        <title>Digital Frame</title>
        <meta
          name="description"
          content="Upload pictures to your Digital Picture Frame."
        />
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <main className={styles.main}>
        <h1 className={styles.title}>
          Digital <span className={styles.colored}>Frame</span>
        </h1>

        <p className={styles.description}>
          Upload pictures to your Digital Picture Frame.
        </p>

        <div className={styles.status}>
          Frame Status:{" "}
          <span
            className={styles.statusValue}
            style={{ color: `${status.color}` }}
          >
            {status.value}
          </span>
        </div>
        <br />
        {status.value == 'Active' ? (
          <div>
            <input ref={img_uri} placeholder="Enter Image URI" height="1rem" className={styles.input}/>
            <button onClick={handleSubmit} className={styles.uploadButton}>
              Upload
            </button>
            <br />
            <br />
            <div className={styles.uploadStatus}>{responseGood ? responseGood : ""}</div>
          </div>
        ) : (
          <div></div>
        )}
      </main>

      <footer className={styles.footer}>
        Powered by
        <span className={styles.logo}>
          <a href="https://saakshaat.me" target="_blank" className={styles.a}>
            Saakshaat
          </a>
        </span>
      </footer>
    </div>
  );
}
