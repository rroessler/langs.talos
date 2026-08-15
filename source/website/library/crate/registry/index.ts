/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Website Modules
import { TOC } from '@/website/components';
import { Assets } from '@/website/assets';
import { Product } from '@/website/product';

/// Package Modules
import { Manifest } from '../manifest';

/** Crates Registry Namespace. */
export namespace Registry {
    //  PUBLIC METHODS  //

    /** Resolves a list of all crates. */
    export function list(): Manifest[] {
        // prepare the source directory of crates
        const source = Assets.crates();

        // filter all the available files now
        return fs
            .readdirSync(source)
            .map(resolve)
            .filter((crate): crate is Manifest => typeof crate === 'object');
    }

    /**
     * Handles resolving crate manifests.
     * @param name                  Name of crate.
     */
    export function resolve(name: string): Manifest | undefined {
        const prefix = `${Product.identifier}:`; // prepare the prefix now
        name = name.startsWith(prefix) ? name.slice(prefix.length) : name;

        // attempt finding the necessary crate now
        const crate = Assets.crates(name, '_crate.jsonc');
        if (name.startsWith('_') || !fs.existsSync(crate)) return;

        // prepare a suitable resolution handler now
        const resolve = (...segments: string[]) => path.resolve(crate, '..', ...segments);

        // attempt parsing the incoming JSONC file now
        return { ...JSON.parse(fs.readFileSync(crate, 'utf-8')), resource: crate, resolve };
    }

    /**
     * Handles transform source table-of-contents.
     * @param source                Source to transform.
     */
    export function transform(source: typeof import('@/website/source').Source.crates, prefix = 'crates') {
        // prepare the base table-of-contents to be used
        const toc = [TOC.seed('Overview'), TOC.seed('Exports')];

        // prepare a set of keyed items
        const keys = new Set<string>();
        const index = `${prefix}/index.mdx`;

        // iteratively update the source files now
        for (const file of source.files) {
            if (file.type === 'meta' || file.path === index) continue;
            (keys.add(file.path.split('/')[1]), (file.data.toc = toc));
        }

        // attempt removing the collapsible items
        for (const key of keys) source.files.push(TOC.meta(key, prefix));
    }
}
